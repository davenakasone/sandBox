EXEC = oo
#LIB_EIGEN = "/usr/local/Cellar/eigen/3.4.0_1/include/eigen3/Eigen/"
COMP = g++ -std=c++11 -Wall

SRC = main.cpp

raw :
	@clear
	@rm -rf $(EXEC)
#@$(COMP) -I $(LIB_EIGEN) -o $(EXEC) $(SRC) 
	$(COMP) -o $(EXEC) $(SRC)
	@echo "compiled [ $(EXEC) ]"

clean :
	@clear
	@rm -rf $(EXEC)


#########~~~~~~~~END>  Makefile
