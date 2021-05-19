function matrix_solve(A,b)
	m, n = size(A)
	x = zeros(n)
	pivot_vals = []
	for pivot_row in 1:min(m,n)
		pivot_val = A[pivot_row,pivot_row]
		push!(pivot_vals, pivot_val)
		for other_row in (pivot_row+1):m
			other_val = A[other_row, pivot_row]
			if other_val != 0
				A[other_row,:] = A[other_row,:].- A[pivot_row,:].*(other_val/pivot_val)
			end
		end
	end
	println(pivot_vals)
end

function null_space(A) 
	m, n = size(A)
	free_cols = []
	for pivot_row in 1:m
		pivot_val = A[pivot_row,pivot_row]
		if pivot_val == 0
			push!(free_cols, pivot_row)
			continue
		end
		for other_row in pivot_row+1:m
			leading_val = A[other_row, pivot_row]
			if leading_val != 0
				A[other_row,:] = A[other_row,:] - A[pivot_row,:].*(leading_val/pivot_val)
			end
		end
	end
	for col in free_cols
		x = zeros(n)
		x[col] = 1
		matrix_solve(A[:,1:(col-1)], A[:,col])
	end
	return A
end

A = [ 1 2 3;
	  4 5 6;
	  7 8 9.0 ]
println(null_space(A))
