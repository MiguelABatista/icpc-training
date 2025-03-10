CXX = g++
CXXFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts

GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

LATEST_CPP = $(shell ls -t *.cpp 2>/dev/null | head -1)
LATEST_BASE = $(basename $(LATEST_CPP))

.PHONY: all clean test

clean:
	rm -f main *.exe *.o temp_output a b c d e f g h i j k l m n

test:
	@if [ -z "$(LATEST_CPP)" ]; then \
		echo "$(RED)No .cpp files found in current directory$(NC)"; \
		exit 1; \
	fi
	@echo "Testing $(LATEST_CPP)..."
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) "$(LATEST_CPP)" -o main
	@for i in in$(LATEST_BASE)[0-9]*; do \
		if [ -f "$$i" ]; then \
			test_num=$${i#in$(LATEST_BASE)}; \
			expected_output="out$(LATEST_BASE)$$test_num"; \
			if [ -f "$$expected_output" ]; then \
				./main < "$$i" > temp_output; \
				if diff -Z -B temp_output "$$expected_output" > /dev/null; then \
					echo "$(GREEN)Test $$test_num: PASSED$(NC)"; \
				else \
					echo "$(RED)Test $$test_num: FAILED$(NC)"; \
					echo "Expected:"; \
					cat "$$expected_output"; \
					echo "Got:"; \
					cat temp_output; \
				fi; \
			fi; \
		fi; \
	done
	@rm -f temp_output main