#!/bin/bash
pid_max=$(cat /proc/sys/kernel/pid_max)
echo "maximum PID value: $pid_max"
