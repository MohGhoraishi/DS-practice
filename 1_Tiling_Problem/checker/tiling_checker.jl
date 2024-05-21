using CSV, Plots, DataFrames
df = DataFrame(CSV.File("text.csv", delim=" "))
directions = df[:,:"d"]
rows = df[:,:"r"] .+ 1
columns = df[:,:"c"] .+ 1
N = Int(sqrt(length(directions) * 3 + 1))
mat = zeros(N, N)
global count = 10
function tile(d, r, c, mat)
    if d==0
        mat[r+1, c] += count
        mat[r, c+1] += count
        mat[r+1, c+1] += count
    elseif d==1
        mat[r+1, c] += count
        mat[r, c] += count
        mat[r+1, c+1] += count
    elseif d==2
        mat[r, c] += count
        mat[r, c+1] += count
        mat[r+1, c+1] += count
    elseif d==3
        mat[r, c] += count
        mat[r, c+1] += count
        mat[r+1, c] += count
    end
    global count = count 
    return mat
end

tile_count = length(directions)
for i in 1:tile_count
    global mat = tile(directions[i], rows[i], columns[i], mat)
end
heatmap(mat, legend = false, aspectratio=1, yflip = true)
#m, n = size(mat)
#vline!(0.5:(n+0.5), c=:black)
#hline!(0.5:(m+0.5), c=:black)