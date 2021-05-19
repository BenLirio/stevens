@enum CMP begin
	LT
	ISO
	EQ
	GT
end
mutable struct Poly
	p::Int
	coef::Array{Int,1}
end

function deg_poly(f)
	leading_zero = 0
	for coef in f.coef
		if coef == 0
			leading_zero += 1
		end
		break
	end
	return length(f.coef)-1-leading_zero
end

function monotize_poly(f)
	f_deg = deg_poly(f)
	f.coef = f.coef[length(f.coef)-f_deg:length(f.coef)]
	f_scale = invmod(f.coef[1], f.p)
	for i in 1:length(f.coef)
		f.coef[i] = mod(f.coef[i]*f_scale, f.p)
	end
end

function normalize!(f)
	for i in 1:(f.p-1)
		if gcd(i, p) != 1
			println("P=$p is invalid, must be a finite field")
			return 
		end
	end
	f = monotize_poly(f)
end

function div_poly(f::Poly, g::Poly)
	if f.p != g.p
		println("f.p=$f.p != g.p=$g.p")
		return
	end
	f_deg = deg_poly(f)
	g_deg = deg_poly(g)
	r = Poly(g.p, copy(g.coef))
	for i in 1:length(g.coef)
		normalize!(r)
		if f_deg > (g_deg+1-i)
			break
		end
		for j in 1:length(r.coef)
			r.coef[j] = r.coef[j] - f.coef[
		end
	end
end

function cmp_poly(f::Poly, g::Poly)
	f_deg = deg_poly(f)
	g_deg = deg_poly(g)
	if (f_deg > g_deg)
		return GT
	end
	if (f_deg < g_deg)
		return LT
	end
	if (f_deg == g_deg)
		if length(f.coef) != length(g.coef)
			println("If polynomials have the same degree they should have the same length")
		end
		for i in 1:length(f.coef)
			if f.coef[i] != g.coef[i]
				return ISO
			end
		end
	end
	return EQ
end

function gcd_poly(f::Poly, g::Poly)
	normalize!(f)
	normalize!(g)
	cmp = cmp_poly(f, g)
	if cmp == LT
		div_poly(f,g)
	end
	if cmp == GT
		div_poly(g,f)
	end
end


p = 5
gcd_poly(Poly(p, [4,-1,3,1,-2]), Poly(p, [4, 0, 1, 0, 0, 0]))

