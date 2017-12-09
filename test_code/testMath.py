from math import *

def test(l1, l2):
	print(l1, l2)
	print("\n")
	theta = l1-l2
	x = ((l2)/(theta) + .5) - ((l2)/(theta) + .5) * cos(theta)
	y = ((l2)/(theta) + .5) * sin(theta)
	print(x)
	print(y)
	print(degrees(theta))
	print("\n")
	print("\n")

test(1.0, .5)
test(.5, 1.0)
test(2.0, .5)
test(.5, 2.0)
test(1.0, 3.5)
test(3.5, 1.0)
test(5, .3) 
test(.3, 5)
test(1.0, 0)
