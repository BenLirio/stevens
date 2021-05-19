using DataFrames
using CSV
data = CSV.read("height_data.csv", DataFrames)
println(data)
