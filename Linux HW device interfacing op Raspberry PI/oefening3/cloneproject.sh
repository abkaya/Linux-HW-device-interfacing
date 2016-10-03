

if [ "$#" -ne 2 ]; then
	echo "Invalid syntax"
	echo "Copies the oefening3 project to a new location with a new name"
	echo "param 1: path to new location"
	echo "param 2: new project name"
	exit -1
fi

mkdir $1 || true
cp * $1
cd $1
make clean
sed -i s/oefening3/$2/g oefening3.cbp
sed -i s/oefening3/$2/g Makefile
sed -i s/oefening3/$2/g cloneproject.sh
mv oefening3.cbp $2.cbp
rm -f *~ || true
rm -f *.workspace || true
rm -f *.layout || true
echo "DONE"

