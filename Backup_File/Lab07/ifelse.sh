if [[ $1 -gt 3 ]] && [[ $1 -lt 7 ]]
then
   echo "$1 is between 3 and 7"
elif [[ $1 =~ "Jeff" ]] || [[ $1 =~ "Roger" ]]
then
   echo "$1 is student in computer engineering"
else
   echo "You entered: $1"
fi
