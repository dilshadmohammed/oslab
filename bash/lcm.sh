#!/bin/bash

# Function to find the Greatest Common Divisor (GCD) using the Euclidean algorithm
gcd() {
    local a=$1
    local b=$2
    while [ $b -ne 0 ]; do
        local temp=$b
        b=$((a % b))
        a=$temp
    done
    echo $a
}

# Function to find the Least Common Multiple (LCM) of two numbers
lcm() {
    local a=$1
    local b=$2
    local gcd_result=$(gcd $a $b)
    local lcm_result=$((a * b / gcd_result))
    echo $lcm_result
}

# Main script starts here

# Check if exactly two arguments are provided
if (($#!=2)); then
    echo "Usage: $0 <number1> <number2>"
    exit 1
fi

# Extract the two numbers from command-line arguments
num1=$1
num2=$2

# Calculate the LCM
result=$(lcm $num1 $num2)

# Print the result
echo "LCM of $num1 and $num2 is: $result"
