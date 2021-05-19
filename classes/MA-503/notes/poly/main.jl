function check()
	for i in 0:2
		for j in 0:2
			for k in 0:2
				for i1 in 0:2
					for j1 in 0:2
						for k1 in 0:2
							if (i * i1)%3 != 1
								continue
							end
							if (k * k1)%3 != 2
								continue
							end
							if ((j * k1) + (k * j1))%3 == 2
								continue
							end
							println("($(i)x^2 + $(j)x + $(k)) * ($(i1)x^2 + $(j1)x + $(k1))")
						end
					end
				end
			end
		end
	end
end

check()
