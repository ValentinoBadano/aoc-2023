f = open("input.txt", "r");
lines = readlines(f)
close(f)

function get_vector(cadena::String)
    match_result = match(r"(\w+), (\w+)", cadena)
    vector_resultado = [match_result.captures[1], match_result.captures[2]]
    return vector_resultado
end

function name(cadena::String)
    match_result = match(r"^\s*([^\s=]+)\s*=", cadena)
    return match_result.captures[1]

end

function find_node(node)
    for line in lines
        match_result = match(Regex("$(node) ="), line)
        if match_result != nothing
            return line
        end
    end
    return nothing
end

instructions = lines[1]
actual_node = find_node("AAA")
steps = 0
not_found = true


println("Starting node $actual_node")
while not_found
    for char in instructions
        actual_vector = get_vector(actual_node)
        if char == 'L'
            global actual_node = find_node(actual_vector[1])
        elseif char == 'R'
            global actual_node = find_node(actual_vector[2])
        end
        global steps += 1
        if name(actual_node) == "ZZZ"
            global not_found = false
            break
        end
        # println("Actual node: $actual_node got here with instruction $char")
    end
end
println("Got to the end in $steps steps")
