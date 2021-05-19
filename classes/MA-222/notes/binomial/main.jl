function factorial(n)
	val::BigInt = 1
	for i in 1:n
		val *= i
	end
	return val
end

function ncr(n, k)
	return factorial(n) / (factorial(n-k) * factorial(k))
end

function pmf(n, k, p)
	return ncr(n,k)*(p^k)*((1-p)^(n-k))
end

function run()
	n::BigInt = 15
	p = 0.75
	val = 0
	for i::BigInt in 11:15
		val += pmf(n, i, p)
	end
	println(val)
end

run()
