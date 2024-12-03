echo "Running the program to get data..."
./getdata.sh

echo "Generating individual data files..."
./datmaker.sh

echo "Generating graphs..."
./plotmaker.sh
