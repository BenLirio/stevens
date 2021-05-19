function determinate(A)
	m, n = size(A)
	dim = m == n ? m : 0
	if dim == 0
		println("Dimension Error")
		return
	end
	if dim == 2
		return A[1,1]*A[2,2] - A[1,2]*A[2,1]
	end
	det = 0
	for col in 1:dim
		det += (-1)^(col%2) *  A[1,col] * determinate(A[2:m, [1:(col-1); (col+1):n]])
	end
	return det
end

A = [ 2 3 3;
	  3 5 4;
	  3 4 5]

B = [	1 2;
		0 3 ]
B_t = [	1 0;
		2 3 ]

C = [	1 2 3 4;
		7 2 7 0;
		3 5 1 9;
		3 1 4 8 ]
R = [	1 1;
		1 2;
		2 1 ]
R_t = [	1 1 2;
		1 2 1 ]
d = determinate(C)
println(d)
