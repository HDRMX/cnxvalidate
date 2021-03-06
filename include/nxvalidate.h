/**
  * This is the public header file for the NeXus file validation library.
	*
	* Copyright: GPL
	*
	* Mark Koennecke, mark.koennecke@psi.ch, and NIAC
	* November 2015
*/

#ifndef __NXVVALIDATE
#define __NXVVALIDATE
#include <nxvhash.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct __NXVContext *pNXVcontext;
/*
 * NXVinit initializes the validation context Mainly
 * installs a default NXDL locator and a default logger.
 * \param nxdlDir The directory where to look for NXDL files
 * \return a pointer to a new validation context. Or NULL on
 * failure.
 */
pNXVcontext NXVinit(const char *nxdlDir);
	/*
 * NXVkill deletes a validation context created with NXVinit
 * \param self The validation context
 */
void NXVkill(pNXVcontext self);


/*
 * This is the signature for a function processing a validation error or
 * information. The function cannot assume that it owns the data in the
 * logEntry structure.
 */
typedef void (*validateLogger)(hash_table *logData, void *userData);

/*
 * NXVsetLogger sets a custom logger for validation. Please note that
 * the user data belongs to the caller. The NXValidate library makes
 * no attempt to delete it.
 * \param self The validation context to set the logger for. Must have
 * been created with NXVinit
 * \param logger The logger to use
 * \param userData any data to pass to the custom logger
 */
void NXVsetLogger(pNXVcontext self, validateLogger logger, void *userData);

/*
 * This is the signature of a function retrieving an application definition.
 * It is supposed to return the content of the application definition as
 * string. Or NULL, if it cannot be located.
 */
typedef char* (*RetrieveNXDL)(char *appDef, void *userData);

/*
 * NXVsetNXDLRetriever sets a user defined function for retrieving
 * application definition data. Please note that the user data is
 * owned by the caller. The NXValidate library makes not attempt
 * to delete it.
 * \param self The validation context to set this retriever for
 * \param retriever The retrieval function
 * \param userData Any data to pass to the retriever.
 */
void NXVsetNXDLRetriever(pNXVcontext self, RetrieveNXDL retriever,
												 void *userData);

/* NXVvalidate runs the validation. Outputs trouble to a log.
* \param self The validation context to run the validation in
* \param dataFile The file to validate
* \param nxdlFile The application definition to validate against. Can be
* NULL, then the validator searches the application definition in the
* NeXus data file.
* \param path The path to the entry to validate in the NeXus file. When NULL,
* default operation applies
* \return 0 when validation succeeds, 1 else.
*/
int NXVvalidate(pNXVcontext self, const char *dataFile,
                const char *nxdlFile, const char *path, const int procroot);

/* NXVgetCounters retrieves the number of errors and warning found in the
 * validation run
 * \param self the validation context
 * \param errCount A pointer to an int variable which will be filled with the
 *        error count
 * \param warnCount A pointer to an int variable which will be filled with the
 *	      warning count
 */
void NXVgetCounters(pNXVcontext self, int *errCount, int *warnCount);
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif
