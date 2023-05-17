all:
	@echo "> Making stack demo"
	@make -C stack --no-print-directory
	@echo "> Making queue demo"
	@make -C queue --no-print-directory

clean:
	@echo "> Cleaning ./bin"
	@rm -rf ./bin
	@mkdir ./bin
