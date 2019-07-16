#!/usr/bin/env bash
export PATH="$PATH:`pwd`/../cmake-build-debug/src/"
echo unif
sh unif-run.sh >unif
echo normal
sh normal-run.sh >normal 
echo zipf
sh zipf-run.sh >zipf
