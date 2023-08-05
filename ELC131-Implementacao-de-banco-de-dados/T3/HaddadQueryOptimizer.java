package ibd.query.optimizer.filter;

import ibd.query.Operation;
import ibd.query.Utils;
import ibd.query.binaryop.BinaryOperation;
import ibd.query.binaryop.Difference;
import ibd.query.sourceop.SourceOperation;
import ibd.query.unaryop.PKFilter;
import ibd.query.unaryop.UnaryOperation;

public class HaddadQueryOptimizer implements FilterQueryOptimizer {

    Operation root;

    public boolean searchNextDifference(PKFilter filter, Operation op) {
        //se não encontrou uma source, ainda há arvore p percorrer, procura mais operações
        if (op instanceof SourceOperation == false) {
            //se é unária, aprofunda mais
            if (op instanceof UnaryOperation) {
                UnaryOperation uop = (UnaryOperation) op;
                return searchNextDifference(filter, uop.getOperation());
            }
            //se é binária, vê se é diferença
            if (op instanceof BinaryOperation) {
                //se é diferença, atualiza cada lado com o filtro
                if (op instanceof Difference) {
                    BinaryOperation bop = (BinaryOperation) op;
                    //atualizando lado esquerdo da diferença com o filtro
                    PKFilter filterLeft = null;
                    try {
                        filterLeft = new PKFilter(bop.getLeftOperation(), null, filter.getComparisonType(), filter.getValue());
                    } catch (Exception e) {
                        throw new RuntimeException(e);
                    }
                    bop.setLeftOperation(filterLeft);
                    //atualizando lado direito da diferença com o filtro
                    PKFilter filterRight = null;
                    try {
                        filterRight = new PKFilter(bop.getRigthOperation(), null, filter.getComparisonType(), filter.getValue());
                    } catch (Exception e) {
                        throw new RuntimeException(e);
                    }
                    bop.setRightOperation(filterRight);
                    return true;
                }
                //se não é diferença, retorna
                else {
                    return false;
                }
            }
        }
        //árvore finalizada, retorna
        return false;
    }

    public void runTree(Operation op, int flag) {
        if (op instanceof UnaryOperation) {
            if (op instanceof PKFilter) {
                Operation filter = op;
                Operation parentOp = op.getParentOperation();
                Operation childOp = ((PKFilter) op).getOperation();
                Boolean result = null;
                try {
                    result = searchNextDifference((PKFilter) filter, op);
                } catch (Exception e) {
                    throw new RuntimeException(e);
                }
                if (result) {
                    if (parentOp == null) {
                        this.root = childOp;
                        childOp.setParentOperation(null);
                    } else {
                        if (parentOp instanceof UnaryOperation) {
                            ((UnaryOperation) parentOp).setOperation(childOp);
                            childOp.setParentOperation(parentOp);
                        }
                        if (parentOp instanceof BinaryOperation) {
                            if (flag == 1) {
                                ((BinaryOperation) parentOp).setLeftOperation(childOp);
                                childOp.setParentOperation(parentOp);
                            }
                            if (flag == 2) {
                                ((BinaryOperation) parentOp).setRightOperation(childOp);
                                childOp.setParentOperation(parentOp);
                            }
                        }
                    }

                }
                runTree(((PKFilter) op).getOperation(), flag);
            } else {
                runTree(((UnaryOperation) op).getOperation(), 0);
            }
        } else if (op instanceof BinaryOperation) {
            runTree(((BinaryOperation) op).getLeftOperation(), 1);
            runTree(((BinaryOperation) op).getRigthOperation(), 2);
        }
    }

    public Operation pushDownFilters(Operation root) {

        this.root = root;

        Operation op = this.root;
        try {
            runTree(op, 0);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }


        return this.root; // o retorno deve ser a operação raiz da árvore
    }
}