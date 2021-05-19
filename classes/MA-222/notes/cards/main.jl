using Random

function choose_cards()
	return shuffle(1:7)[1:3]
end

function gen_pdf()
	W = []	
	n_trials = 100000
	for i in 1:n_trials
		push!(W, sum(choose_cards()))
	end
	vals = Dict()
	for w in W
		vals[w] = get(vals, w, 0) + 1/n_trials
	end
	outcomes = zeros(Float64, 18)
	for (w,val) in vals
		outcomes[w] = val
	end
	return outcomes
end
