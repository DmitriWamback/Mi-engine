FILE=$1

OUTPUT=$(/Library/Developer/CommandLineTools/usr/bin/lua $FILE)
echo $OUTPUT