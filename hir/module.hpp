#pragma once

/**
 * hir is the step below the ast which is made from lowering the ast 
 * and on which we can perform typechecking and convert to MIR for borrowchecking and possibly
 * optimizations
 * 
 * hir is a lowered version of the ast with more information of everything
 * So we fist lower the ast (desuggering if neccesary)
 * and then we perform the typechecking and lowering to MIR 
 */