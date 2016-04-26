import os, sys, subprocess, argparse

sizesS = [10, 20, 30, 40, 50]
sizesM = [100, 150, 200, 250]
sizesL = [500, 750, 1000]
num_runs = 1

def gen_cmd(size):
	n = str(size)
	cmd = ['./main', '-d', 'n' + n + '.dat', '-g', 'n' + n + '.graph', '-n', n]
	return cmd

def usage():
	sys.stderr.write('Usage: python run_tests.py [S | M | L]')
	sys.exit()
	
def main():
	if len(sys.argv) < 2:
		usage()
	else:
		size_t = sys.argv[1].lower()
		
	if size_t == 's':
		sizes = sizesS
	elif size_t == 'm':
		sizes = sizesM
	elif size_t == 'l':
		sizes = sizesL
	else:
		usage()
		
	cmds = []
	for i in sizes:
		os.system('python gen_data.py ' + str(i) + ' > n' + str(i) + '.dat')
		cmds.append(gen_cmd(i))
	for cmd in cmds:
		for i in range(num_runs):
			with open('results.txt', 'a') as out:
				subprocess.call(cmd, stdout=out)
#
# Call this module as a main program
if __name__ == '__main__':
	main()