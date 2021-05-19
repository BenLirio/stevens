a = 1258
b = 527

large = a
small = b
u = 1
x = 0
print("Large\tU\tSmall\tX")
while True:
	if small == 0:
		v = (large - a*u)/b
		#print(a, "*", u, "+", b, "*", v, "=", large)
		break


	quotient = large//small
	remainder = large%small
	s = u - quotient * x
	u = x
	large = small
	x = s
	small = remainder
	print(f"{large}\t{u}\t{small}\t{(large-a*u)//b}")
