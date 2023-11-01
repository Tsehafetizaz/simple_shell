#!/bin/bash

# initialize variables
project_folder="."
total_errors=0
shell_executable="simple_shell"
builtins=("cd" "echo" "exit" "...") # Add built-in commands as needed
special_chars=("\"" "'" "\`" "\\" "*" "&" "#")

# Function to log a passed check
pass() {
	echo -e "\e[32mPASS:\e[0m $1"
}

# Function to log a failed check
fail() {
	echo -e "\e[31mFAIL:\e[0m $1"
	((total_errors++))
}

# Check for README.md file
if [ ! -f "$project_folder/README.md" ]; then
	fail "README.md file is missing"
else
	pass "README.md found"
fi

# Check for AUTHORS file
if [ ! -f "$project_folder/AUTHORS" ]; then
	fail "AUTHORS file is missing"
else
	pass "AUTHORS file found"
fi

# Check for simple shell executable
if [ ! -f "$project_folder/$shell_executable" ]; then
	fail "$shell_executable executable is missing"
else
	pass "$shell_executable executable found"
fi

# Check for Betty style in C files
while IFS= read -r -d '' file; do
	echo "Checking Betty style for $file"
	betty-style.pl "$file"
	if [ $? -ne 0 ]; then
		fail "Betty style check failed for $file"
	else
		pass "Betty style check passed for $file"
	fi

	betty-doc.pl "$file"
	if [ $? -ne 0 ]; then
		fail "Betty documentation check failed for $file"
	else
		pass "Betty documentation check passed for $file"
	fi

	# Check for direct PATH usage
	if grep -q "\bPATH\b" "$file"; then
		fail "Direct PATH usage found in $file"
	else
		pass "No direct PATH usage in $file"
	fi

	# Check for built-in implementation
	for builtin in "${builtins[@]}"; do
		if grep -q -w "^\s*\(void\|int\|char\+\s\+\)*$builtin\s*(" "$file"; then
			fail "Built-in $builtin possibly implemented in $file"
		fi
	done

	# Check for special character handling
	for char in "${special_chars[@]}"; do
		if grep -q "[$char]" "$file"; then
			fail "Special character $char found in $file, ensure proper handling"
		fi
	done

	# Check for execve usage
	if grep -q -w "execve" "$file"; then
		pass "execve found in $file"
	else
		fail "execve not found in $file, ensure it's part of the shell's core"
	fi

	# Check for environ passed to execve
	if grep -q -w "execve(.*, .*, environ)" "$file"; then
		pass "environ passed to execve in $file"
	else
		fail "environ not passed to execve in $file, ensure proper environment handling"
	fi

done < <(find "$project_folder" -name "*.c" -print0)

# Check for header file include guards
while IFS= read -r -d '' file; do
	echo "Checking include guards for $file"
	if ! grep -q "#ifndef" "$file" || ! grep -q "#define" "$file" || ! grep -q "#endif" "$file"; then
		fail "Include guards missing in $file"
	else
		pass "Include guards found in $file"
	fi
done < <(find "$project_folder" -name "*.h" -print0)

# Summary
if [ $total_errors -eq 0 ]; then
	echo -e "\e[32mAll checks passed successfully!\e[0m"
else
	echo -e "\e[31m$total_errors errors found\e[0m"
	exit 1
fi
