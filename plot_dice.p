# The graphic title
set title 'Expected Value when Rolling Three Dice and Taking the Maximum of the Three'
# labels:
set xlabel "Die faces"
set ylabel "Expected Value"
#set limit for y axis
#set yrange [0:10]
#set location of legend
set key at graph 0.3, 0.95
#plot the graphic
plot "dice_expected_values.csv" using 1:2 title "expected value in 3 rolls", \
     "dice_expected_values.csv" using 1:3 title 'Increase in expected value'
# finish:
pause -1 "Hit any key to continue"
