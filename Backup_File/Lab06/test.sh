if [[ $1 = "+" ]]
then
   let x=($2+$3)
   echo "$2 $1 $3 = "$x
elif [[ $1 = "-" ]]
then
   let x=($2-$3)
   echo "$2 $1 $3 = "$x
else
   echo "You entered: $1 not math"
fi
