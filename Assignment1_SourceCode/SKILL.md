---
name: assignment-todo-completion
description: Complete starter-code TODOs in a coding assignment, implement the required behavior, and verify with the provided compiler/tests before finishing.
---

# Assignment TODO Completion Workflow

## Purpose
Use this skill when a project contains explicit TODO markers, a starter implementation, and a test harness or expected-output files. The goal is to finish the missing logic without changing the public interfaces, preserve the assignment contract, and verify the result with evidence.

## When to use
- A repository has one or more `TODO` comments in source files.
- The assignment includes a README or build instructions.
- The user wants the missing implementation completed and the project validated.

## Workflow

1. Read the assignment contract first.
   - Open the README and any public headers to confirm the required signatures and behavior.
   - Identify which files belong to which part of the assignment.
   - Treat the headers as the contract: do not modify signatures unless the task explicitly allows it.

2. Trace the required behavior before editing.
   - Read the relevant implementation file and surrounding tests or expected output.
   - Map each TODO to the contract described in the header, README, or test assertions.
   - Prefer root-cause fixes over superficial patching.

3. Implement the missing logic in small, focused steps.
   - Complete one TODO or closely related group at a time.
   - Keep the change minimal and consistent with the project style.
   - Preserve pointer semantics, ownership rules, and error handling described by the spec.

4. Validate compilation immediately.
   - Run the most targeted build command for the affected component.
   - Fix compiler errors before moving on to deeper logic checks.

5. Validate behavior with the provided tests.
   - Run the provided test target when available.
   - If the assignment includes expected output files, run the program and compare actual output against the expected files.
   - If something fails, inspect the exact mismatch and correct the root cause.

6. Confirm completion with evidence.
   - Ensure the relevant test command exits successfully.
   - Check that there are no remaining TODO markers in the validated files.
   - Report the command and result, not just a belief that it works.

## Decision points

- If the failure is compiler-related, fix the signature or implementation mismatch before logic debugging.
- If the failure is runtime logic, compare actual output to expected behavior and trace the incorrect function.
- If the assignment defines pointer ownership rules, follow them exactly; do not leak or double-delete memory.
- If the project includes both unit tests and program-output checks, do both unless the assignment only calls for one.

## Quality gate
The work is complete only when all of the following are true:
- The code compiles without the relevant errors.
- The provided tests pass or the expected output matches.
- The implementation satisfies the public contract defined by the headers and README.
- The output and behavior match the assignment expectations.

## Example prompts
- Fix all TODOs in this assignment and verify with the provided tests.
- Complete the missing implementations for the matrix operations and run the output diff check.
- Finish the starter C++ project without changing the public API and confirm the behavior.

## Related customizations
- Create a stricter debugging skill for pointer/memory safety in C++ assignments.
- Create a verification skill for output-diff validation against expected files.
- Create a unit-test-first skill for projects that require red-to-green validation.
