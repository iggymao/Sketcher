#include "stdafx.h"
#include <stdarg.h>
#include <time.h>
#include <assert.h>
#include <iostream>

#include "../Headers/LogManager.h"


GLenum gl_params[]= 
{
	GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
	GL_MAX_CUBE_MAP_TEXTURE_SIZE,
	GL_MAX_DRAW_BUFFERS,
	GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
	GL_MAX_TEXTURE_IMAGE_UNITS,
	GL_MAX_TEXTURE_SIZE,
	GL_MAX_VARYING_FLOATS,
	GL_MAX_VERTEX_ATTRIBS,
	GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
	GL_MAX_VERTEX_UNIFORM_COMPONENTS,
	GL_MAX_VIEWPORT_DIMS,
	GL_STEREO,
};

const char* gl_param_names[] = 
{
	"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
	"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
	"GL_MAX_DRAW_BUFFERS",
	"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
	"GL_MAX_TEXTURE_IMAGE_UNITS",
	"GL_MAX_TEXTURE_SIZE",
	"GL_MAX_VARYING_FLOATS",
	"GL_MAX_VERTEX_ATTRIBS",
	"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
	"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
	"GL_MAX_VIEWPORT_DIMS",
	"GL_STEREO",
};

// constructor
LogManager::LogManager()
{
	printf("\nLog Manager default constructor...");

	SetID(2000);								// sets the LogManagerID to 1,000;

	MemberInfo = new LogInfo;				// creates an empty ShaderInfo list
	MemberInfo->LogID = -1;
	MemberInfo->LogType = LOG_TYPE_UNDEFINED;
	MemberInfo->strLogFilename = "Undefined";
	MemberInfo->next = NULL;

	// Since nothing is currently stored, the first and last members are pointed to the previous value (NULL);
	firstMemberInfo = MemberInfo;		// point the first member to the previous value
	lastMemberInfo = MemberInfo;		// point the last member to the previous value
}

// A generic log file function
bool LogManager::gl_log (char *filename, char *message, ...) 
{
	va_list argptr;
	FILE* file = fopen(filename, "a");
	if(!file) {
		fprintf(stderr,"\nERROR: could not open GL_LOG_FILE %s file for appending\n", GL_LOG_FILE);
		return false;
	}
	va_start (argptr, message);
	vfprintf(file, message, argptr);
	va_end (argptr);
	fclose(file);
	return true;
}

void LogManager::gl_log_params()
{
		char *logfile;
		logfile = GL_LOG_FILE;

		gl_log (logfile, "\nGL Context Params:");
		// integers - only works if the order is 0-10 integer return types
		for (int i = 0; i<10; i++)
		{
			int v = 0;
			glGetIntegerv(gl_params[i], &v);
			gl_log(logfile, "%s %i\n", gl_param_names[i], v);
		}
		// others
		int v[2];
		v[0] = v[1] = 0;
		glGetIntegerv(gl_params[10], v);
		gl_log(logfile, "%s %i %i\n", gl_param_names[10], v[0], v[1]);
		unsigned char s = 0;
		glGetBooleanv(gl_params[11], &s);
		gl_log(logfile, "%s %u\n", gl_param_names[11], (unsigned int)s);
		gl_log(logfile,"-------------------------------------\n");

	return;
}

void LogManager::Initialize()
{
	printf("\n     Intialize the Log Manager");
	AddLog(MemberInfo, LOG_TYPE_MAIN, LOG_FILE);
	AddLog(MemberInfo, LOG_TYPE_OPENGL, GL_LOG_FILE);
	AddLog(MemberInfo, LOG_TYPE_SHADER, SHADER_LOG_FILE);
}

void LogManager::ShowDetails(struct LogInfo *head)
{
	LogInfo *list = head;

	printf("\nShowing details of the contents stored by the log manager...");

	if (head->LogID == -1)
	{
		printf("\n...No LogInfo found at this time...");
		return;
	}

	while(list)
	{
		printf("\nMember ID:     %i ", list->LogID);
		printf("\nMember Type:   %i ", list->LogType);
		printf("\nstrLogFilename: %s ", list->strLogFilename.c_str());
		printf("\n-------------------------------------------");
		list=list->next;
	}
	return;
}

bool LogManager::restart_logs()
{
	printf("\n     Restarting Logs...");
	LogInfo *cur;
	cur = MemberInfo;
	while(cur)
	{
		// delete existing logs
		if( remove( cur->strLogFilename.c_str()) != 0 )
			printf( "ERROR deleting file:  %s", cur->strLogFilename.c_str() );
		else
			printf("\n	%s logfile deleted.", cur->strLogFilename.c_str());

		// then open the newfile for writing
		FILE* file = fopen(cur->strLogFilename.c_str(), "w");
		if (!file) {
			fprintf(stderr, "ERROR: could not open GL_LOG_FILE log file %s for writing\n", cur->strLogFilename);
			return false;
		}
		time_t now = time (NULL);
		char* date = ctime(&now);
		fprintf(file,"LogFile Created at local time %s", date);
		fclose(file);
		cur=cur->next;  // move to the next entry
	}
	return true;
}

void LogManager::AddLog(struct LogInfo *head, int type, std::string logfilename)
{
	printf("\n	   Adding a log to the logs manager list...");

	LogInfo *newLog = new LogInfo;
	newLog->LogID = ((lastMemberInfo->LogID)+1);
	newLog->LogType = type;
	newLog->strLogFilename = logfilename;
	newLog->next = NULL;
	
	LogInfo *curLog = head;

	if (head->LogID == -1)
	{
		MemberInfo = newLog;
		lastMemberInfo = newLog;
		return;
	}
	while (curLog)
	{
//		printf ("\nID: %i      Type:  %i     Filename: %s", curLog->LogID, curShader->LogType, curLog->strFilename.c_str());
		if(curLog->next == NULL)
		{
			curLog->next = newLog;
			lastMemberInfo = curLog->next;
			return;
		}
		curLog = curLog->next;
	}
	return;
}


void deleteLinkedList(struct LogInfo *head)
{
	// Need to make a functional routine to delete a linked list in order to
	// implement the Destroy() option total.  Skipping for now.

	//LogInfo *cur = head; 
	//while(!(cur->next==NULL)) {
	//	cur = cur->next;
	//	delete head;
	//	head = cur_next;
	//}
	return;
}
struct LogInfo* LogManager::searchLogInfo(struct LogInfo *head, int logtype) 
{
	LogInfo *cur = head;
	while(cur) {
		if(cur->LogType == logtype)
			return cur;
		cur = cur->next;
	}
	printf("\nNo log found in the manager of type %i", logtype);
	return cur;
}

void LogManager::Destroy()
{
	printf("\nINCOMPLETE:  Destroying the Log Manager");
	// Need to make a functional routine to delete a linked list in order to
	// implement the Destroy() option total.  Skipping for now.
	//deleteLinkedList(&MemberInfo);
}





//
//bool LogManager::gl_log_err (const char* message, ...) {
//	va_list argptr;
//	FILE* file = fopen (GL_LOG_FILE, "a");
//	if (!file)
//	{
//		fprintf(stderr,"ERROR: could not open GL_LOG_FILE %s file for appending\n", GL_LOG_FILE);
//		return false;
//	}
//	va_start(argptr, message);
//	vfprintf(file, message, argptr);
//	va_end(argptr);
//	va_start (argptr, message);
//	vfprintf(stderr, message, argptr);
//	va_end (argptr);
//	fclose (file);
//	return true;
//}
//

//
//void LogManager::glfw_error_callback (int error, const char* description)
//{
//	gl_log_err ("GLFW ERROR: code %i msg: %s\n", error, description);
//}