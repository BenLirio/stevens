function exp(b, e, m)
	cur = 1
	for i in 1:e
		cur = (cur * b) % m
	end
	return cur
end

function order(g, n)
	order = 1
	cur = g
	for i in 1:(n-1)
		if cur == 1
			break
		end
		cur = (cur * g) % n
		order += 1
	end
	return order
end

function gen()
	p = 83
	q = 101
	n = p*q
	g = 2
	r1 = rand(1:n)
	r2 = rand(1:n)
	g1 = exp(g, r1*(p-1), n)
	g2 = exp(g, r2*(q-1), n)
	return (n, g1, g2)
end

function run()
	p = 83
	q = 101
	n = p*q
	g = 2
	println(order(g, n))
	g1_vals = []
	g2_vals = []
	for i in 1:100
		r1 = i
		r2 = i
		g1 = exp(g, r1*(p-1), n)
		g2 = exp(g, r2*(q-1), n)
		push!(g1_vals, g1)
		push!(g2_vals, g2)
	end
	unique!(g1_vals)
	unique!(g2_vals)
	sort!(g1_vals)
	sort!(g2_vals)
	for g1 in g1_vals
		for g2 in g2_vals
			if g1 == g2
				println(g1)
			end
		end
	end
end

function decrypt()
	n, g1, g2 = gen()
	g1_order = 0
	g2_order = 0
	for i in 2:n
		if exp(g1, i, n) == 1
			g1_order = i
			break
		end
	end
	for i in 2:n
		if exp(g2, i, n) == 1
			g2_order = i
			break
		end
	end
	println("|g1|=$g1_order, |g2|=$g2_order")
end
decrypt()
