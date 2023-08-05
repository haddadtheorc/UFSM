/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ibd.table.management;

import ibd.table.block.Block;
import ibd.table.record.Record;
import ibd.table.Table;

public class HeapTableHaddad extends Table {

    public HeapTableHaddad(String folder, String name, int pageSize, boolean override) throws Exception {
        super(folder, name, pageSize, override);
    }

    private Block findFirstFreeBlock(Record record) throws Exception {
        int id = getFirstHeapBlock();
        while (id != -1) {
            Block block = getBlock(id);
            if (block.fits(record.len())) {
                return block;
            } else {
                id = block.next_heap_block_id;
            }
        }
        return null;
    }

    private boolean checkEmptyHeap() throws Exception {
        if (getFirstHeapBlock() == -1) {
            return true;
        }
        return false;
    }

    private Block createFirstHeapBlock() throws Exception {
        Block newBlock = addBlock();
        setFirstHeapBlock(newBlock.getPageID());
        setLastHeapBlock(newBlock.getPageID());
        dataFile.writePage(newBlock);
        return newBlock;
    }

    private Block createNewHeapBlock() throws Exception {
        Block newBlock = addBlock();
        getBlock((getLastHeapBlock())).next_heap_block_id = newBlock.getPageID();
        dataFile.writePage(getBlock(getLastHeapBlock()));
        newBlock.prev_heap_block_id = getLastHeapBlock();
        newBlock.next_heap_block_id = -1;
        dataFile.writePage(newBlock);
        setLastHeapBlock(newBlock.getPageID());
        return newBlock;
    }

    private void removeHeapBlock(int targetId) throws Exception {
        int idFirst = getFirstHeapBlock();
        int idLast = getLastHeapBlock();
        Block block = getBlock(targetId);
        if(targetId == idFirst){
            if(block.next_heap_block_id != null){
                setFirstHeapBlock(block.next_heap_block_id);
            }
        }
        else{
            if(block.prev_heap_block_id != null){
                getBlock(block.prev_heap_block_id).next_heap_block_id = block.next_heap_block_id;
                dataFile.writePage(getBlock(block.prev_heap_block_id));
            }
        }
        if(targetId == idLast){
            if(block.prev_heap_block_id != null){
                setFirstHeapBlock(block.prev_heap_block_id);
            }
        }
        else{
            if(block.next_heap_block_id != null){
                getBlock(block.next_heap_block_id).prev_heap_block_id = block.prev_heap_block_id;
                dataFile.writePage(getBlock(block.next_heap_block_id));
            }
        }
    }

    private boolean checkBlockHeap(int targetId) throws Exception {
        int id = getFirstHeapBlock();
        while (id != -1) {
            if (id == targetId) {
                return true;
            }
            id = getBlock(id).next_heap_block_id;
        }
        return false;
    }

    private void addHeapBlock(int blockId) throws Exception {
        getBlock(getLastHeapBlock()).next_heap_block_id = blockId;
        dataFile.writePage(getBlock(getLastHeapBlock()));
        getBlock(blockId).prev_heap_block_id = getLastHeapBlock();
        dataFile.writePage(getBlock(blockId));
        setLastHeapBlock(blockId);
    }

    @Override
    protected Record addRecord(Record record) throws Exception {
        // Se a heap está vazia, cria o primeiro bloco dela e a retorna
        if (checkEmptyHeap()) {
//            System.out.println("HEAP VAZIA");
            Block newBlock = createFirstHeapBlock();
            return addRecord(newBlock, record);
        } else {
            // Senão, procura o primeiro bloco que cabe o record
            Block b = findFirstFreeBlock(record);
            // Não existindo, cria um bloco novo e o retorna
            if (b == null) {
//                System.out.println("SEM BLOCO VAZIO, CRIANDO UM");
                Block newBlock = createNewHeapBlock();
//                System.out.println("BLOCO " + newBlock.getPageID() + " CRIADO");
                return addRecord(newBlock, record);
            }
            // Existindo, retorna o bloco livre
            else {
//                System.out.println("BLOCO " + b.getPageID() + " LIVRE, DEVOLVENDO");
                // Quando um registro é inserido no bloco escolhido, e o bloco fica sem espaço suficiente para 400 bytes deve-se remover o bloco da lista, caso ele esteja nela
                if (b.getPageSize() - (b.getUsedSpace() + record.len()) < 410) {
//                    System.out.println("REMOVENDO BLOCO CHEIO");
                    removeHeapBlock(b.getPageID());
                }
                return addRecord(b, record);
            }
        }
    }

    @Override
    protected Record removeRecord(Block block, Record record) throws Exception {
        record = super.removeRecord(block, record);
        // Quando um registro é removido, e o bloco onde ele estava fica com espaço livre suficiente para 400 bytes
        if (block.getPageSize() - block.getUsedSpace() >= 400) {
            // Deve-se inserir o bloco na lista heap, caso ele ainda não esteja inserido
            if (!checkBlockHeap(block.getPageID())) {
                addHeapBlock(block.getPageID());
            }
        }
        if (record == null) {
            return null;
        }
        return record;
    }
}
