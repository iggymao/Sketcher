#include "stdafx.h"
#include <iostream>
//#include "../Headers/Main.h"
//#include "../Headers/Mesh.h"
#include "../Headers/Volume.h"
#include "../Headers/Mesh.h"

/*
GLuint Volume::next_id = -1;			// set the initial value at the start of the program

// A constructor for our volume class
Volume::Volume()
{
	//NumMeshes = 0;
	//VolumeType = VOLUME_UNDEFINED;
	//VolTargetWindow = 0;
	printf("\nVolume constructor...");

	//MeshID = Volume::next_id++; 
	//printf("\nVolume::next_id++ %i",Volume::next_id);
	VolumeID = next_volume_id();
	printf("\nVolume::next_id++ %i",Volume::next_id);


	VolumeInfo *newVolInfo = new VolumeInfo;
	newVolInfo->MeshID = -1;		// copy the MeshID into the VolumeInfo record

	newVolInfo->MeshInsertPt[0] = NULL;
	newVolInfo->MeshInsertPt[1] = NULL;
	newVolInfo->MeshInsertPt[2] = NULL;
	newVolInfo->MeshTanVect[0] = NULL; 	// a tangent vector for the orientation of a member mesh
	newVolInfo->MeshTanVect[1] = NULL;
	newVolInfo->MeshTanVect[2] = NULL;
	newVolInfo->MeshNormVect[0] = NULL;	// a normal vector for the orientation of a member mesh
	newVolInfo->MeshNormVect[1] = NULL;
	newVolInfo->MeshNormVect[2] = NULL;
	newVolInfo->MeshBinormVect[0] = NULL;	// a binormal vector for the orientation of a member mesh
	newVolInfo->MeshBinormVect[1] = NULL;
	newVolInfo->MeshBinormVect[2] = NULL;

	newVolInfo->previous = NULL;
	newVolInfo->next = NULL;

	MemberMesh = newVolInfo;
//	CurrentMeshNumber = -1;

}

// Initialize the class using a simple shape parameter defined in application.h
void Volume::Initialize()
{
	printf("\nInitialize volume.");
	printf("\nINCOMPLETE:  install initial values");

	ShowVolumeDetails(MemberMesh);  // verify the that the volume Details are empty.
	printf("\nShowing the empty volume details (hopefully)");

	// a test mesh
	Mesh *testmesh;
	testmesh = new Mesh;
	testmesh->Initialize();

	//       mesh     <---coords-->  <-- tan vec--> <-- norm ---> <-- binorm --->
	AddMesh(testmesh, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
	AddMesh(testmesh, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

	// display the results of the testmesh
	testmesh->ShowMeshVertexDetails(testmesh->MeshVertexInfo);
	testmesh->ShowMeshIndexDetails(testmesh->MeshIndexInfo);

	ShowVolumeDetails(MemberMesh);
}

// adds a mesh to the MemberMesh linked list
int Volume::AddMesh(Mesh *mesh, GLfloat x, GLfloat y, GLfloat z, GLfloat tan_i, GLfloat tan_j, GLfloat tan_k, GLfloat norm_i, GLfloat norm_j, GLfloat norm_k, GLfloat binorm_i, GLfloat binorm_j, GLfloat binorm_k)
{
	printf("\nAdding mesh to volume.");
	printf("\nAdding mesh #%i to list.",mesh->GetMeshID());
	VolumeInfo *newVolInfo = new VolumeInfo;
	newVolInfo->MeshID = mesh->GetMeshID();		// copy the MeshID into the VolumeInfo record
	printf ("meshID: mesh->GetMeshID(): %i", mesh->GetMeshID());


	newVolInfo->MeshInsertPt[0] = x;
	newVolInfo->MeshInsertPt[1] = y;
	newVolInfo->MeshInsertPt[2] = z;
	newVolInfo->MeshTanVect[0] = tan_i; 	// a tangent vector for the orientation of a member mesh
	newVolInfo->MeshTanVect[1] = tan_j;
	newVolInfo->MeshTanVect[2] = tan_k;
	newVolInfo->MeshNormVect[0] = norm_i;	// a normal vector for the orientation of a member mesh
	newVolInfo->MeshNormVect[1] = norm_j;
	newVolInfo->MeshNormVect[2] = norm_k;
	newVolInfo->MeshBinormVect[0] = binorm_i;	// a binormal vector for the orientation of a member mesh
	newVolInfo->MeshBinormVect[1] = binorm_j;
	newVolInfo->MeshBinormVect[2] = binorm_k;

	newVolInfo->previous = NULL;
	newVolInfo->next = NULL;
	
	VolumeInfo *curVolInfo = MemberMesh;

	if (MemberMesh->MeshID == -1)
	{
		MemberMesh = newVolInfo;
		lastVolumeInfo = newVolInfo;
		return newVolInfo->MeshID;
	}
	while (curVolInfo)
	{
		if(curVolInfo->next == NULL)
		{
			curVolInfo->next = newVolInfo;
			lastVolumeInfo = curVolInfo->next;
			return newVolInfo->MeshID;
		}
		curVolInfo = curVolInfo->next;
	}
	return newVolInfo->MeshID;
}

void Volume::ShowVolumeDetails(struct VolumeInfo *head)
{
	printf("\n===============================================================");
	printf("\nShow details of the volume data for Volume #: %i", GetVolumeID());
	VolumeInfo *list = head;
	
	if (head->MeshID == -1)
	{
		printf("\n...No Volume Info added at this time...");
		return;
	}

	while(list)
	{
		printf("\nMeshID: %i ", list->MeshID);		// copy the MeshID into the VolumeInfo record
		printf("\nMeshInsertPt:      X: %f   Y: %f  Z: %f", list->MeshInsertPt[0], list->MeshInsertPt[1], list->MeshInsertPt[2]);
		printf("\nMeshTanVector:     i: %f   j: %f  k: %f", list->MeshTanVect[0],list->MeshTanVect[1],list->MeshTanVect[2]);
		printf("\nMeshNormVector:    i: %f   j: %f  k: %f", list->MeshNormVect[0],list->MeshNormVect[1],list->MeshNormVect[2]);
		printf("\nMeshBinormVector:  i: %f   j: %f  k: %f", list->MeshBinormVect[0],list->MeshBinormVect[1],list->MeshBinormVect[2]);
		list=list->next;
	}
	printf("\n===============================================================");
	return;
}

// deletes a mesh to the MemberMesh linked list
void Volume::DeleteMesh()
{
	printf("\nDeleting mesh from volume.");
}

// search the MemberMesh linked list for a particular member mesh
void Volume::SearchMesh()
{
	printf("\nSearching for mesh in member list.");
}

void Volume::CreateVAO()
{

}

void Volume::CreateVBO()
{

}

void Volume::CreateEBO()
{
	printf("\n		Creating an EBO");
}

*/

//void Volume::Initialize(int shape_code)
//{
//	printf("\nInitializing the volume...");
//
//	VolTargetWindow = WINDOW_VIEW_UNDEFINED;
//
//	switch(shape_code)
//	{
//		case VOLUME_UNDEFINED:
//		{
//
//			break;
//		}
//		case VOLUME_RIGHT_PRISM:
//		{
//
//			MemberMesh[0] = new Mesh;
//			MemberMesh[0]->CreateMesh(WINDOW_VIEW2, MESH_SQUARE, (GLfloat)1.50, (GLfloat)-1.5, (GLfloat)1.0);
//			NumMeshes = 1; 
//
//			break;
//		}
//
//		case VOLUME_AREA:
//		{
//			MemberMesh[0] = new Mesh;
//			MemberMesh[0]->CreateMesh(WINDOW_VIEW2, MESH_TRIANGLE, (GLfloat)0.750, (GLfloat)0.50, (GLfloat)1.0);
//			NumMeshes = 1; 
///*
//			//Create the Mesh (test)
//			MemberMesh[0] = new Mesh;
//			MemberMesh[0]->CreateMesh(WINDOW_VIEW1, MESH_TRIANGLE, 1.5, 0.5, 0.0);
//			MemberMesh[1] = new Mesh;
//			MemberMesh[1]->CreateMesh(WINDOW_VIEW1, MESH_TRIANGLE, 0.5, 1.0, 0.0);
//			MemberMesh[2] = new Mesh;
//			MemberMesh[2]->CreateMesh(WINDOW_VIEW2, MESH_TRIANGLE, 0.5, 0.5, 0.0);
//			MemberMesh[3] = new Mesh;
//			MemberMesh[3]->CreateMesh(WINDOW_VIEW2, MESH_TRIANGLE, 0.75, -0.5, 0.0);
//			NumMeshes = 4;
//*/
//			break;
//		}
//		default:
//		{
//			printf("\nUnkown volume type...");
//			NumMeshes = -1;
//			break;
//		}
//	}
//	NumVAO = NumMeshes;
//	NumVBO = NumMeshes;
//	return;
//}

//void Volume::RenderVolume(int target_window, AppWindow **WinID_array)
////void Volume::RenderVolume(AppWindow **p_array, GLuint **VolVBO_ID, GLuint **VolVAO_ID)
//{
//	printf("\nRendering the volume...");
//
////	GLFWwindow *Window;
//
//	// search for windows belonging to a target window
//	for (int j=0; j< MAX_WINDOWS; j++)
//	{
//		int i=0;
//		cout << "\n======================================================";
//		cout << "\n Window #: " << j << endl;
//		for (i=0;i<NumMeshes;i++)
//		{
//			// if the current window is the same as the TargetWindow draw it
//			if (target_window == j)
//			{
//				/*
//				Window = (*(WinID_array+j))->GetWindow();
//
//				// Make sure the window is valid, if not, throw an error.
//				if ((Window == nullptr) || (target_window >= MAX_WINDOWS) )
//				{
//					fprintf(stderr, "\nInvalid Window found in ModelMesh.cpp RenderModel() function");
//					return;
//				}
//				*/
//
//				cout << "\nFound a window " << target_window;
//				MemberMesh[i]->RenderMesh(&MemberMesh[i]);							// the Mesh array to be parsed
//				//TempMesh[count] = MemberMesh[i];		
////				cout << "\ni: " << i << " -- j: " << j << " -- Match #: " << count << " found...adding to TempMesh[]..";
////				cout << "\nMemberMesh[" << count << "] -- MeshType: " << MemberMesh[count]->MeshType << endl;
//			}
////		MemberMesh[i]->RenderMesh(p_array, MemberMesh, NumMeshes );
//		}
//		cout << "\n=======================================================";
//		
///*
//		if (!(count < 1))  // if at least one mesh matched, 
//		{
//			for (int i=0;i<count;i++)
//			{
//				cout << "\nPassing " << (count) << " meshes to RenderMesh() function";
//				//TempMesh[0]->RenderMesh(
//				//	WinID_array,							// the WindowID array
//				//	MemberMesh,							// the Mesh array to be parsed
//				//	count,							// Mesh qty to render	
//				//	2,									// Number of VAO's used per window
//				//	2									// Number of VBO's used per window
//				//);
//
////				MemberMesh[0]->RenderMesh(&MemberMesh[0]);							// the Mesh array to be parsed
//
//			}
//		}
//		*/
//	}
//
///*
//	// To swap the buffers...cycle through each of the AppWindows.
//	for(int i=0;i<MAX_WINDOWS;i++)
//	{
////		TargetWindow = MemberMesh[i]->TargetWindow;
////		cout << "Volume MemberMesh[" << i << "],  Type #: " << MemberMesh[i]->MeshType << " to TargetWindow #: " << TargetWindow;
//		Window = (*(WinID_array+i))->GetWindow();
//getchar();
//
//		glfwSwapBuffers(Window);
////		getchar();
//	}
//*/
////	for(int i=0;i<NumMeshes;i++)
////	{
////		MemberMesh[i]->DestroyMesh();
//////		MemberMesh[i]->RenderMesh(p_array, MemberMesh, NumMeshes );
////	}
//}
