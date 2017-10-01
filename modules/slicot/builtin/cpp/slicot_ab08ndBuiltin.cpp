//=============================================================================
// LICENCE_BLOCK_BEGIN
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// LICENCE_BLOCK_END
//=============================================================================
// Generated by Nelson Interface Generator 1.0.0
//=============================================================================
#include "Error.hpp"
#include "slicot_ab08ndBuiltin.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
#ifdef __cplusplus
extern "C"
{
#endif
extern int ab08nd_ ( const char *EQUIL, int N, int M, int P,const double *A, int LDA,const double *B, int LDB,const double *C, int LDC,const double *D, int LDD, int &NU, int &RANK, int &DINFZ, int &NKROR, int &NKROL, int *INFZ, int *KRONR, int *KRONL, double *AF, int LDAF, double *BF, int LDBF, double TOL, int *IWORK, double *DWORK, int LDWORK, int &INFO);
#ifdef __cplusplus
}
#endif
//=============================================================================
// [NU, RANK, DINFZ, NKROR, NKROL, INFZ, KRONR, KRONL, AF, BF, INFO] = slicot_ab08nd(EQUIL, N, M, P, A, B, C, D, TOL)
//=============================================================================
ArrayOfVector Nelson::SlicotGateway::slicot_ab08ndBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (nLhs > 11)
    {
        Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    if (argIn.size() != 9)
    {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }

    // INPUT VARIABLES

    ArrayOf EQUIL = argIn[0];
    std::string EQUIL_string = EQUIL.getContentAsCString();
    const char* EQUIL_char = EQUIL_string.c_str();
    ArrayOf N = argIn[1];
    int N_scalar = N.getContentAsInteger32Scalar();
    ArrayOf M = argIn[2];
    int M_scalar = M.getContentAsInteger32Scalar();
    ArrayOf P = argIn[3];
    int P_scalar = P.getContentAsInteger32Scalar();
    ArrayOf A = argIn[4];
    A.promoteType(NLS_DOUBLE);
    double *A_ptr = (double*)A.getDataPointer();
    ArrayOf B = argIn[5];
    B.promoteType(NLS_DOUBLE);
    double *B_ptr = (double*)B.getDataPointer();
    ArrayOf C = argIn[6];
    C.promoteType(NLS_DOUBLE);
    double *C_ptr = (double*)C.getDataPointer();
    ArrayOf D = argIn[7];
    D.promoteType(NLS_DOUBLE);
    double *D_ptr = (double*)D.getDataPointer();
    ArrayOf TOL = argIn[8];
    double TOL_scalar = TOL.getContentAsDoubleScalar();

    // IN/OUT VARIABLES


    // OUTPUT VARIABLES

    ArrayOf NU_output = ArrayOf::int32VectorConstructor(1);
    int *NU_output_ptr = (int*)NU_output.getDataPointer();
    ArrayOf RANK_output = ArrayOf::int32VectorConstructor(1);
    int *RANK_output_ptr = (int*)RANK_output.getDataPointer();
    ArrayOf DINFZ_output = ArrayOf::int32VectorConstructor(1);
    int *DINFZ_output_ptr = (int*)DINFZ_output.getDataPointer();
    ArrayOf NKROR_output = ArrayOf::int32VectorConstructor(1);
    int *NKROR_output_ptr = (int*)NKROR_output.getDataPointer();
    ArrayOf NKROL_output = ArrayOf::int32VectorConstructor(1);
    int *NKROL_output_ptr = (int*)NKROL_output.getDataPointer();
    ArrayOf INFZ_output = ArrayOf::int32Matrix2dConstructor((indexType)1, (indexType)N.getContentAsInteger32Scalar());
    int *INFZ_output_ptr = (int*)INFZ_output.getDataPointer();
    ArrayOf KRONR_output = ArrayOf::int32Matrix2dConstructor((indexType)1, (indexType)std::max(N.getContentAsInteger32Scalar(), M.getContentAsInteger32Scalar()) + 1);
    int *KRONR_output_ptr = (int*)KRONR_output.getDataPointer();
    ArrayOf KRONL_output = ArrayOf::int32Matrix2dConstructor((indexType)1, (indexType)std::max(N.getContentAsInteger32Scalar(), M.getContentAsInteger32Scalar()) + 1);
    int *KRONL_output_ptr = (int*)KRONL_output.getDataPointer();
    ArrayOf AF_output = ArrayOf::doubleMatrix2dConstructor((indexType)std::max(1, N.getContentAsInteger32Scalar() + M.getContentAsInteger32Scalar()), (indexType)N.getContentAsInteger32Scalar() + std::min(P.getContentAsInteger32Scalar(), M.getContentAsInteger32Scalar()));
    double *AF_output_ptr = (double*)AF_output.getDataPointer();
    ArrayOf BF_output = ArrayOf::doubleMatrix2dConstructor((indexType)N.getContentAsInteger32Scalar() + M.getContentAsInteger32Scalar(), (indexType)std::max(1, N.getContentAsInteger32Scalar() + P.getContentAsInteger32Scalar()));
    double *BF_output_ptr = (double*)BF_output.getDataPointer();
    ArrayOf INFO_output = ArrayOf::int32VectorConstructor(1);
    int *INFO_output_ptr = (int*)INFO_output.getDataPointer();

    // LOCAL VARIABLES

    int LDA_local = std::max(1, N.getContentAsInteger32Scalar());
    int LDB_local = std::max(1, N.getContentAsInteger32Scalar());
    int LDC_local = std::max(1, P.getContentAsInteger32Scalar());
    int LDD_local = std::max(1, P.getContentAsInteger32Scalar());
    int LDAF_local = std::max(1, N.getContentAsInteger32Scalar() + M.getContentAsInteger32Scalar());
    int LDBF_local = std::max(1, N.getContentAsInteger32Scalar() + P.getContentAsInteger32Scalar());
    int *IWORK_local = (int*)ArrayOf::allocateArrayOf(NLS_INT32, 1 * std::max(M.getContentAsInteger32Scalar(), P.getContentAsInteger32Scalar()));
    double *DWORK_local = (double*)ArrayOf::allocateArrayOf(NLS_DOUBLE, 1 * std::max(std::max(M.getContentAsInteger32Scalar(), P.getContentAsInteger32Scalar()), N.getContentAsInteger32Scalar()) + std::max(3 * std::max(M.getContentAsInteger32Scalar(), P.getContentAsInteger32Scalar()) - 1, N.getContentAsInteger32Scalar() + std::max(N.getContentAsInteger32Scalar(), P.getContentAsInteger32Scalar())));
    int LDWORK_local = std::max(std::max(M.getContentAsInteger32Scalar(), P.getContentAsInteger32Scalar()), N.getContentAsInteger32Scalar()) + std::max(3 * std::max(M.getContentAsInteger32Scalar(), P.getContentAsInteger32Scalar()) - 1, N.getContentAsInteger32Scalar() + std::max(M.getContentAsInteger32Scalar(), P.getContentAsInteger32Scalar()));

    // ASSIGN OUTPUT VARIABLES

    if (nLhs > 0)
    {
        retval.push_back(NU_output);
    }
    if (nLhs > 1)
    {
        retval.push_back(RANK_output);
    }
    if (nLhs > 2)
    {
        retval.push_back(DINFZ_output);
    }
    if (nLhs > 3)
    {
        retval.push_back(NKROR_output);
    }
    if (nLhs > 4)
    {
        retval.push_back(NKROL_output);
    }
    if (nLhs > 5)
    {
        retval.push_back(INFZ_output);
    }
    if (nLhs > 6)
    {
        retval.push_back(KRONR_output);
    }
    if (nLhs > 7)
    {
        retval.push_back(KRONL_output);
    }
    if (nLhs > 8)
    {
        retval.push_back(AF_output);
    }
    if (nLhs > 9)
    {
        retval.push_back(BF_output);
    }
    if (nLhs > 10)
    {
        retval.push_back(INFO_output);
    }

    return retval;
}
//=============================================================================
