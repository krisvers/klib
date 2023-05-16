all:
	@echo "> Making stack demo"
	@make -C stack --no-print-directory

clean:
	@echo "> Cleaning ./bin"
	@rm -rf ./bin
	@mkdir ./bin
