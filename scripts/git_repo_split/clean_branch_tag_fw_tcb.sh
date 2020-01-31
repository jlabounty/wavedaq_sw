#!/bin/bash

# Removing Branches (always keep master and develop):
#git branch -D debug/FixCollectorThread
git branch -D debug/ch0_readout
git branch -D debug/pkg_buffer_test
git branch -D develop_revD
git branch -D develop_revg
#git branch -D feature/DCBPisa
#git branch -D feature/TCB100to80
#git branch -D feature/TCBAutoLockSerdes
#git branch -D feature/TCBSerdesMux
git branch -D feature/bootloader_caching
git branch -D feature/dcb_develop_pisa
git branch -D feature/plb_drp_interface
git branch -D feature/sequential_drs_read
git branch -D feature/swissfel_setup
git branch -D feature/uart_interrupt
git branch -D feature/uart_with_large_rxtx_fifo
git branch -D feature/wds_binarydump
git branch -D feature/wds_trigger_readout

# Removing Tags:
git tag -d ADC_Bitflip_Problem_Solved
git tag -d First_commit_on_hw_rev_B
git tag -d Last_commit_on_hw_rev_A
git tag -d WD_HW_Rev_C_-_Last_Commit_bevore_moving_to_Rev_D
git tag -d WD_HW_Rev_D_-_First_commit_after_moving_to_Rev_D
#git tag -d WD_HW_Rev_D_-_Last_Commit_bevore_moving_to_Rev_E
git tag -d WD_HW_Rev_E_-_First_Commit_after_moving_to_Rev_E
git tag -d final_state_without_bootloader
git tag -d old-wds
git tag -d original_directory_structure
