#!/bin/bash

main_repo_url=git@bitbucket.org:twavedaq/wavedaq_main_draft.git
#main_repo_url=git@bitbucket.org:twavedaq/wavedaq_main.git

submodule_branch=master

submodule_dirs=(
  doc
  fw/cmb
  fw/dcb
  fw/tcb
  fw/wdb
  hw
  sw
)

submodule_remotes=(
  git@bitbucket.org:twavedaq/wavedaq_doc_draft.git
  git@bitbucket.org:twavedaq/wavedaq_fw_cmb_draft.git
  git@bitbucket.org:twavedaq/wavedaq_fw_dcb_draft.git
  git@bitbucket.org:twavedaq/wavedaq_fw_tcb_draft.git
  git@bitbucket.org:twavedaq/wavedaq_fw_wdb_draft.git
  git@bitbucket.org:twavedaq/wavedaq_hw_draft.git
  git@bitbucket.org:twavedaq/wavedaq_sw_draft.git
)

#submodule_remotes=(
#  git@bitbucket.org:twavedaq/wavedaq_doc.git
#  git@bitbucket.org:twavedaq/wavedaq_fw_cmb.git
#  git@bitbucket.org:twavedaq/wavedaq_fw_dcb.git
#  git@bitbucket.org:twavedaq/wavedaq_fw_tcb.git
#  git@bitbucket.org:twavedaq/wavedaq_fw_wdb.git
#  git@bitbucket.org:twavedaq/wavedaq_hw.git
#  git@bitbucket.org:twavedaq/wavedaq_sw.git
#)

# Check if repository exists
if git-remote-url-reachable "$main_repo_url"
then
  printf "*** Source GIT repository: ${main_repo_url}\n"
else
  printf "*** Error: source URL ${main_repo_url} is not a GIT repository\n"
  return 1
fi

local_dir=${main_repo_url/#*@*:}
#printf "Local Directory: ${local_dir}\n"
local_dir=${local_dir/#*\/}
#printf "Local Directory: ${local_dir}\n"
local_dir=${local_dir/%.*}
printf "*** Local Directory: ${local_dir}\n"

# Checkout (empty) main repository
printf "\n*** Cloning ${main_repo_url} --> repository should be new (i.e. empty) !!!\n"
git clone ${main_repo_url} ${local_dir}
cd ${local_dir}

# Create folders
printf "\n*** Creating folders in ${local_dir}\n"
#mkdir doc
mkdir fw
#mkdir hw
#mkdir sw

# Create subfolders
#printf "*** Creating subfolders in ${local_dir}\n"
#mkdir fw/cmb
#mkdir fw/dcb
#mkdir fw/tcb
#mkdir fw/wdb

# Add submodules
printf "\n*** Adding submodules\n"
NR_OF_SRS=${#submodule_remotes[@]}
for ((i=0;i<$NR_OF_SRS;i++))
do
  git submodule add -b master ${submodule_remotes[i]} ${submodule_dirs[i]}
done

# Init and Update submodules
printf "\n*** Initializing and Updating submodules\n"
git submodule update --init --recursive

# Set submodule branches
printf "\n*** Adjusting submodule branches\n"
NR_OF_SRS=${#submodule_dirs[@]}
for ((i=0;i<$NR_OF_SRS;i++))
do
  # change to submodule dir
  cd ${submodule_dirs[i]}
  # checkout branch
  git checkout ${submodule_branch}
  # pull branch
  git pull
  # Return to main repository directory
  lvls_str="${submodule_dirs[i]//[^\/]}"
  lvls="${#lvls_str}"
  lvls=$((lvls+1))
  for ((j=0;j<${lvls};j++)); do cd ..; done
done

# Stage changes (add)
git add .

# Commit and push main repository
printf "\n*** Commit and Push ${main_repo_url} [n]? "
read clearence
if [ "$clearence" == "y" ] || [ "$clearence" == "yes" ]
then
  printf "\n*** Commiting initial state to ${main_repo_url}...\n"
  git commit -m "Initial submodule setup"
  printf "\n*** Pushing commit to ${main_repo_url}...\n"
  git push origin --all
else
  printf "Commit and push skipped!!!\n"
fi

cd ..

printf "=== DONE ===\n\n"
