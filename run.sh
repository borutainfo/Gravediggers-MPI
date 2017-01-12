#!/usr/bin/env bash
mpirun -default-hostfile none -hostfile ./config/hosts.conf -np 1 ./bin/gravediggers