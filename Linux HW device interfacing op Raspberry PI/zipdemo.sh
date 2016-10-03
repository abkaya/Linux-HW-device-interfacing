if [ "$#" -ne 1 ]; then
	echo "Invalid syntax"
	echo "zip demo directory"
	echo "param 1: password"
	exit -1
fi

zip -rP $1 demo.zip demo
history -c && history -w


