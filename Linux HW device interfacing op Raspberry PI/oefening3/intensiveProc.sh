#!/bin/bash
#dd from /dev/zero to /dev/null for each core, therefore 4 times for the RPi3.
fulload() { 
dd if=/dev/zero of=/dev/null | 
dd if=/dev/zero of=/dev/null | 
dd if=/dev/zero of=/dev/null | 
dd if=/dev/zero of=/dev/null  
}; 

fulload; 
read; 
killall dd