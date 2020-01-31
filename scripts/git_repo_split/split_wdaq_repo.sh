#!/bin/bash

if [ "$#" -lt 3 ]
then
  printf "Usage: $(basename "$0") src-git dst-git split-folder [branch-tag-script]\n\n"
  printf "Script to export (split) a GIT repository folder to a separate GIT repository\n"
  printf "\nwhere:\n"
  printf "  src-git           URL of original (source) GIT repository remote\n"
  printf "  dst-git           URL of destination GIT repository remote\n"
  printf "  split-folder      subfolder to split\n"
  printf "  branch-tag-script script to remove unused tags/branches with\n"
  printf "                    git tag -d <tag-name>\n"
  printf "                    git branch -D <branch-name>\n\n"
  return 1
fi

## Returns errlvl 0 if $1 is a reachable git remote url
git-remote-url-reachable() {
    git ls-remote "$1" CHECK_GIT_REMOTE_URL_REACHABILITY >/dev/null 2>&1
}

src_url=$1
dst_url=$2
split_dir=$3

if [ "$#" -eq 4 ]
then
  branch_tag_script=$4
fi

working_branch=master

printf "\n"

if git-remote-url-reachable "$src_url"
then
  printf "*** Source GIT repository: ${src_url}\n"
else
  printf "*** Error: source URL ${src_url} is not a GIT repository\n"
  return 1
fi

if git-remote-url-reachable "$dst_url"
then
  printf "*** Destination GIT repository: ${dst_url}\n"
else
  printf "*** Error: destination URL ${dst_url} is not a GIT repository\n"
  return 1
fi

printf "\n*** Folder to split: ${split_dir}\n"

local_dir=${dst_url/#*@*:}
#printf "Local Directory: ${local_dir}\n"
local_dir=${local_dir/#*\/}
#printf "Local Directory: ${local_dir}\n"
local_dir=${local_dir/%.*}
printf "*** Local Directory: ${local_dir}\n"

original_dir=${src_url/#*@*:}
#printf "Local Directory: ${original_dir}\n"
original_dir=${original_dir/#*\/}
#printf "Local Directory: ${original_dir}\n"
original_dir=${original_dir/%.*}
printf "*** Source Directory: ${original_dir}\n"

# Check if source repository is already there
# If not: clone source repository
if [ -d "${original_dir}" ]
then
  printf "\n*** Original repository directory ${original_dir} found --> skip cloning\n"
  # Check if local directory exists
  if [ -d "${local_dir}" ]
  then
    # Check if directory is empty
    if [ "$(ls -A $DIR)" ]
    then
      printf "*** Error: Local directory ${local_dir} exists and is not empty. Cannot continue\n"
      return 1
    fi
  fi
  mkdir ${local_dir}
else
  # Check if directory exists
  if [ -d "${local_dir}" ]
  then
    # Check if directory is empty
    if [ "$(ls -A $DIR)" ]
    then
      printf "*** Error: Local directory ${local_dir} exists and is not empty. Cannot clone\n"
      return 1
    fi
  fi

  # Clone source repository
  printf "\n*** Cloning ${src_url}\n"
  git clone --mirror ${src_url} ${original_dir}

  cd ${original_dir}

#  # Load branches to be migrated into split repository
#  printf "\n*** Retrieving all branches\n"
#  for b in `git branch -r | grep -v -- '->'`; do git branch --track ${b##origin/} $b; done
#
#  # Checking out working branch
#  printf "\n*** Checking out branch ${working_branch}\n"
#  git checkout ${working_branch}
#
#  # Init and Update submodules
#  printf "\n*** Initializing and Updating submodules\n"
#  git submodule update --init --recursive

  # Strip source remote
  printf "\n*** Stripping original remote\n"
  git remote -v
  git remote rm origin
  ## to remove more than one remote use:
  #git remote | xargs -n1 git remote remove
  ## not necessary in our case since we have a fresh clone with the default remote (origin)

  cd ..
fi

printf "\n*** Copying original repository from ${original_dir} to ${local_dir}\n"
cp -rf ${original_dir}/. ${local_dir}
cd ${local_dir}

printf "\n*** Delete unwanted branches and tags\n"
. ../${branch_tag_script}

printf "\n*** Filtering out files\n"
# Remove files and commits not used in the split repository (--tag-name-filter cat --prune-empty)
# This is the actual splitting
git filter-branch --tag-name-filter cat --prune-empty --subdirectory-filter ${split_dir} -- --all

printf "\n*** Cleaning up by discarding obsolete data\n"
# Remove backup reflogs to definitely free space
git reset --hard
git for-each-ref --format="%(refname)" refs/original/ | xargs -n 1 git update-ref -d
git reflog expire --expire=now --all
git gc --aggressive --prune=now

printf "\n*** Adding remote ${dst_url}...\n"
# Add remote of split repository
git remote add origin ${dst_url}

printf "\n*** Active GIT remotes:\n"
git remote -v

#printf "\n*** Push ${split_dir} to ${dst_url} [n]? "
#read clearence
#if [ "$clearence" == "y" ] || [ "$clearence" == "yes" ]
if (false)
then

  printf "\n*** Pushing Content to ${dst_url}...\n"
  # Push data
  git push origin --all --follow-tags
else
  printf "Push skipped!!!\n"
fi

cd ..
printf "**************************************************\n"
