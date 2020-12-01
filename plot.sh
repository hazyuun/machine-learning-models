#!/bin/bash
if [ "$1" == "--lin-reg" ]
then
	gnuplot --persist gp_scripts/gp_reg_script
else
	gnuplot --persist gp_scripts/gp_cla_script
fi
gnuplot --persist gp_scripts/gp_metric_script
