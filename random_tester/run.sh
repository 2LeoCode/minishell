#!/bin/bash

at cmd_file | awk 'BEGIN { getline; bash < print $0 } { bash < print $0 }'
