/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ibd.query.binaryop;

import ibd.query.Operation;
import ibd.query.Tuple;
import ibd.query.binaryop.BinaryOperation;
import ibd.table.Table;

import java.util.Objects;

public class HaddadDifference extends BinaryOperation {

    public Operation op1, op2;

    Tuple tupleA, tupleB, tupleToReturn;

    boolean op2Finished;

    public HaddadDifference(Operation op1, Operation op2) throws Exception {
        super(op1, op2);
        this.op1 = op1;
        this.op2 = op2;
    }

    public HaddadDifference(Operation op1, String sourceName1, Operation op2, String sourceName2) throws Exception {
        super(op1, sourceName1, op2, sourceName2);
        this.op1 = op1;
        this.op2 = op2;
    }


    @Override
    public void open() throws Exception {
        super.open();
        this.op1.open();
        this.op2.open();
        this.op2Finished = false;
        this.tupleToReturn = null;
    }


    @Override
    public Tuple next() throws Exception {
        if (tupleToReturn == null) {
            Tuple t = this.findTuple();
            if (t != null) {
                return t;
            } else {
                throw new Exception("NO MORE RECORDS TO ITERATE THROUGH");
            }
        }
        else{
            Tuple returnTuple = this.tupleToReturn;
            this.tupleToReturn = null;
            return returnTuple;
        }

    }

    @Override
    public boolean hasNext() throws Exception {

        if (tupleToReturn != null) {
            return true;
        }
        else{
            Tuple t = this.findTuple();
            if (t != null) {
                this.tupleToReturn = t;
                return true;
            } else {
                return false;
            }
        }
    }

    public Tuple findTuple() throws Exception {

        //se ainda há registros no op1, segue
        if (op1.hasNext()) {
            // se op2 não tem mais registros, avança A e salva a tupla p retornar
            if (this.op2Finished) {
                this.tupleA = op1.next();
                return this.tupleA;
            } else{
                //se ainda há registros no op2, segue,
                if (op2.hasNext()) {
                    if (this.tupleA == null) {
                        this.tupleA = op1.next();
                    }
                    if (this.tupleB == null) {
                        this.tupleB = op2.next();
                    }
                    //enquanto houverem registros no op2, percorre
                    while (op1.hasNext() && op2.hasNext()) {

                        Long pkA = this.tupleA.sourceTuples[tupleIndex1].record.getPrimaryKey();
                        Long pkB = this.tupleB.sourceTuples[tupleIndex1].record.getPrimaryKey();

                        //System.out.println("comparando " + this.tupleA.sourceTuples[tupleIndex1].record.getPrimaryKey() + " com " + this.tupleB.sourceTuples[tupleIndex1].record.getPrimaryKey());

                        //se a PK de A for maior que a de B, .next em B
                        if (pkA.compareTo(pkB) > 0) {
                            //System.out.println("maior");
                            this.tupleB = op2.next();
                        }
                        //se a PK de A for igual a de B, está em ambos, .next A e B
                        else if (pkA.compareTo(pkB) == 0) {
                            //System.out.println("igual");
                            this.tupleA = op1.next();
                            this.tupleB = op2.next();
                        }
                        //se a PK de A for menor que a de B, está na diferença, .next A
                        else if ((pkA.compareTo(pkB) < 0)){
                            //System.out.println("menor");
                            Tuple returnTuple = tupleA;
                            this.tupleA = op1.next();
                            return returnTuple;
                        }
                    }

                    //se op1 acabou, encerra
                    if (!op1.hasNext()) return null;
                    //se op2 acabou, marca como finalizado
                    if (!op2.hasNext()) {
                        this.op2Finished = true;
                        if(this.tupleA.sourceTuples[tupleIndex1].record.getPrimaryKey() < this.tupleB.sourceTuples[tupleIndex1].record.getPrimaryKey()){
                            Tuple returnTuple = tupleA;
                            this.tupleA = op1.next();
                            return returnTuple;
                        }
                        else{
                            this.tupleA = op1.next();
                            return this.tupleA;
                        }
                    }
                }
                //marca op2 como finalizado
                else {
                    this.op2Finished = true;
                }
            }
            if(op1.hasNext()){
                this.tupleA = op1.next();
                return this.tupleA;
            }
            else{
                return null;
            }

        }
        //se não há mais registros em p1
        else {
            return null;
        }
    }

    @Override
    public String toString() {
        return "HaddadDifference";
    }
}
