#WILL FIND OUT ALL THE .IN FILES IN THE FOLDER AND LIST IT
cd ../test/vfstestdata2
ls -a *.in > ../../listOfFiles
cd ../../result

#WILL READ LINE BY LINE AND POPULATE THE ARRAY
count=0
clear
while read line
do
  arr[count]=$line  
  #echo ${arr[$count]}
  count=$((count+1))
done < ../listOfFiles


#REMOVES WHATEVER WILL BE THERE EARLIER
ml=$(make -f ../build/Makefile)
#FOR LOOP TO RUN ALL THE SCRIPTS
for i in {0..305} 
do 
echo $((i)) ${arr[i]}
x=$(./../bin/vfs_group08 ../test/vfstestdata2/${arr[i]})
echo "$x";
echo $'\n';
done

var=0
c=0
echo 'Segmentation Faults are there in the following scripts:' $'\n'
while read line
do
  if [ "$line" = "" ]
   then
  	var=$((var+1))
  	c=$((c+1))
  	continue
  else
	  if [ $c -gt 2 ] 
	    then
	    	echo $memory
	  fi  	
	  	c=0	
  fi
  memory=$line	  
done < ../output.txt
var=$((var-612))
echo 'No: of Segmentation Faults are ' "$((var-1))";

# Use of ./
#REMOVES WHATEVER WILL BE THERE EARLIER
#rm ../bin/*
#mk=$(make -f ../build/Makefile)
#echo $mk
#As for the use of -lt rather than <, that's just part of the syntax of [ (i.e., the test command). It uses = and != for string equality and inequality -eq, -ne, -lt, -le, -gt, and -ge for numbers. As @Malvolio points out, the use of < would be inconvenient, since it's the input redirection operator.
rm ../result/*; 
