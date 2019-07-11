#!/usr/bin/env bash
echo unif
sh unif-run.sh >unif
echo normal
sh normal-run.sh >normal 
echo zipf
sh zipf-run.sh >zipf
