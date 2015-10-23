echo "starting esavmp at..." >> log/experiment01.log
date >> log/experiment01.log
./optimalvmp input/3x5.vmp >> log/experiment01.log
echo "stopping esavmp at..." >> log/experiment01.log
date >> log/experiment01.log
cp -fr results results.3x5
make init

echo "starting esavmp at..." >> log/experiment01.log
date >> log/experiment01.log
./optimalvmp input/4x8.vmp >> log/experiment01.log
echo "stopping esavmp at..." >> log/experiment01.log
date >> log/experiment01.log
cp -fr results results.4x8
make init