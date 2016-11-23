#include <sys/uio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string.h>
#include "../include/Memory.h"

Memory *gMemory = new Memory();

bool Memory::Process(char* processName) {
	// TODO: Currently, PID is located by piping the output of pgrep. A more
	// effective and less clunky way should be found in the future.
	unsigned long child_pid;
	int pipe_fd[2];
	pipe(pipe_fd);

	// Child process sends the requested PID to the pipe.
	if ((child_pid = fork()) == 0) {
		close(STDOUT_FILENO);
		dup(pipe_fd[1]);
		execlp("pgrep", "pgrep", processName, NULL);
		exit(0);
	}

	close(pipe_fd[1]);
	waitpid(child_pid, NULL, WUNTRACED | WCONTINUED);

	// Parent process reads the PID as a string, for evaluation.
	char PID_str[256];
	char buffer;
	for (int i = 0; read(pipe_fd[0], &buffer, 1) > 0; i++) {
		PID_str[i] = buffer;
	}
	close(pipe_fd[0]);

	// Convert the information to a number, to get the true PID.
	Memory::hPID = atoi(PID_str);
}

template <class cData>
cData Memory::Read(unsigned long dwAddress) {
	cData returnValue = 0;

	struct iovec returnDataAddress;
	returnDataAddress.iov_base = (void*) &returnValue;
	returnDataAddress.iov_len = sizeof(cData);

	struct iovec processDataAddress;
	processDataAddress.iov_base = (void*) dwAddress;
	processDataAddress.iov_len = sizeof(cData);

	process_vm_readv(Memory::hPID, &returnDataAddress, 1, &processDataAddress, 1, 0);
}

template <class cData>
void Memory::Write(unsigned long dwAddress, cData value) {
	struct iovec returnDataAddress;
	returnDataAddress.iov_base = (void*) &value;
	returnDataAddress.iov_len = sizeof(cData);

	struct iovec processDataAddress;
	processDataAddress.iov_base = (void*) dwAddress;
	processDataAddress.iov_len = sizeof(cData);

	process_vm_writev(Memory::hPID, &returnDataAddress, 1, &processDataAddress, 1, 0);
}

unsigned long Memory::getPID() {
	return Memory::hPID;
}
