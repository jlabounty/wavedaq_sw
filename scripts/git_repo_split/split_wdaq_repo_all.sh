#!/bin/bash

original_repo="git@bitbucket.org:twavedaq/wavedaq.git"
echo "Original repository: $original_repo"

folders_to_split=(
#  hardware
  software
  docs
  firmware/CMB
  firmware/DCB
  firmware/TCB
  firmware/WD2
)

split_repo_remotes=(
#  git@bitbucket.org:twavedaq/wavedaq_hw.git
  git@bitbucket.org:twavedaq/wavedaq_sw.git
  git@bitbucket.org:twavedaq/wavedaq_doc.git
  git@bitbucket.org:twavedaq/wavedaq_fw_cmb.git
  git@bitbucket.org:twavedaq/wavedaq_fw_dcb.git
  git@bitbucket.org:twavedaq/wavedaq_fw_tcb.git
  git@bitbucket.org:twavedaq/wavedaq_fw_wdb.git
)
#split_repo_remotes=(
##  git@bitbucket.org:twavedaq/wavedaq_hw_draft.git
#  git@bitbucket.org:twavedaq/wavedaq_sw_draft.git
#  git@bitbucket.org:twavedaq/wavedaq_doc_draft.git
#  git@bitbucket.org:twavedaq/wavedaq_fw_cmb_draft.git
#  git@bitbucket.org:twavedaq/wavedaq_fw_dcb_draft.git
#  git@bitbucket.org:twavedaq/wavedaq_fw_tcb_draft.git
#  git@bitbucket.org:twavedaq/wavedaq_fw_wdb_draft.git
#)

clean_scripts=(
#  clean_branch_tag_hw.sh
  clean_branch_tag_sw.sh
  clean_branch_tag_doc.sh
  clean_branch_tag_fw_cmb.sh
  clean_branch_tag_fw_dcb.sh
  clean_branch_tag_fw_tcb.sh
  clean_branch_tag_fw_wdb.sh
)

NR_OF_SRS=${#split_repo_remotes[@]}
for ((i=0;i<$NR_OF_SRS;i++))
do
  if [ "$1" == clean ]
  then
    local_dir=${split_repo_remotes[i]/#*@*:}
    #printf "Local Directory: ${local_dir}\n"
    local_dir=${local_dir/#*\/}
    #printf "Local Directory: ${local_dir}\n"
    local_dir=${local_dir/%.*}
    if [ -d "${local_dir}" ]
    then
      printf "Deleting ${local_dir}\n"
      rm -rf "${local_dir}"
    else
      printf "Directory not found: ${local_dir}\n"
    fi
  else
    . ./split_wdaq_repo.sh ${original_repo} ${split_repo_remotes[i]} ${folders_to_split[i]} ${clean_scripts[i]}
  fi
done
printf "=== DONE ===\n\n"
