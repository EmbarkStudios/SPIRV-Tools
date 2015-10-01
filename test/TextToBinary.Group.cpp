// Copyright (c) 2015 The Khronos Group Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and/or associated documentation files (the
// "Materials"), to deal in the Materials without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Materials, and to
// permit persons to whom the Materials are furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Materials.
//
// MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
// KHRONOS STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS
// SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT
//    https://www.khronos.org/registry/
//
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.

// Assembler tests for instructions in the "Group Instrucions" section of the
// SPIR-V spec.

#include "UnitSPIRV.h"

#include "gmock/gmock.h"
#include "TestFixture.h"

namespace {

using spvtest::EnumCase;
using spvtest::MakeInstruction;
using ::testing::Eq;

// Test GroupOperation enum

using GroupOperationTest = spvtest::TextToBinaryTestBase<
    ::testing::TestWithParam<EnumCase<spv::GroupOperation>>>;

TEST_P(GroupOperationTest, AnyGroupOperation) {
  std::string input =
      "%result = OpGroupIAdd %type %scope " + GetParam().name() + " %x";
  EXPECT_THAT(CompiledInstructions(input),
              Eq(MakeInstruction(spv::OpGroupIAdd,
                                 {1, 2, 3, GetParam().value(), 4})));
}

// clang-format off
#define CASE(NAME) { spv::GroupOperation##NAME, #NAME}
INSTANTIATE_TEST_CASE_P(TextToBinaryGroupOperation, GroupOperationTest,
                        ::testing::ValuesIn(std::vector<EnumCase<spv::GroupOperation>>{
                            CASE(Reduce),
                            CASE(InclusiveScan),
                            CASE(ExclusiveScan),
                        }));
#undef CASE
// clang-format on

// TODO(dneto): OpAsyncGroupCopy
// TODO(dneto): OpWaitGroupEvents
// TODO(dneto): OpGroupAll
// TODO(dneto): OpGroupAny
// TODO(dneto): OpGroupBroadcast
// TODO(dneto): OpGroupIAdd
// TODO(dneto): OpGroupFAdd
// TODO(dneto): OpGroupFMin
// TODO(dneto): OpGroupUMin
// TODO(dneto): OpGroupSMin
// TODO(dneto): OpGroupFMax
// TODO(dneto): OpGroupUMax
// TODO(dneto): OpGroupSMax

}  // anonymous namespace
