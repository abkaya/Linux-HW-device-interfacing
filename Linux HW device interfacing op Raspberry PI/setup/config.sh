if [ "$#" -ne 1 ]; then
	echo "Invalid syntax"
	echo "Sets up raspberry pi for 5-embedded systems"
	echo "param 1: # of the board"
	exit -1
fi

sudo cp wpa_supplicant.conf /etc/wpa_supplicant
sudo cp hostname.emb$1 /etc/hostname 
sudo cp hosts.emb$1 /etc/hosts
sudo cp interfaces.emb$1 /etc/network/interfaces

sync
echo "DONE"

echo "Manual steps still needing to be accomplished:"
echo "Enable I²C ports in raspi-config"
echo "Disable serial port login"

