#scriptname:shell_one
#writer:leishouguo
#select what you do

#!/bin/bash

echo "Welocme!$LOGNAME,the time is: $(date +%T) "
echo ""
echo "the cal of the month........................c"
echo "Edit File..............................................e"
echo "Exit.......................................................q"

echo "Input your choice:"
read choice
  case $choice in
        c|C) echo "enter month:"
               read month
               echo "enter year"
               read year
               cal  $month $year
               set n+=1
                ;;
        e|E) echo "Enter file name:"
               read file
                if  [[ -e $file ]]
               	then
                   vi $file
                   set n+=1
                else
                   echo 'the file no exist'
                   exit 1
                fi
              ;;
        q|Q)  echo "Bye"
                exit 1;;
        *) echo "illegal option"
           echo "$choice is not of the choices!"   
esac
echo "the end!"
