package cn.mrcode.study.dsalgtutorialdemo.datastructure.tree;

import org.junit.Test;

/**
 * ������������
 */
public class ThreadedBinaryTreeTest {
    class HeroNode {
        public int id;
        public String name;
        public HeroNode left;
        public HeroNode right;
        /**
         * ��ڵ�����ͣ�0����������1��ǰ���ڵ�
         */
        public int leftType;
        /**
         * �ҽڵ�����ͣ�0����������1����̽ڵ�
         */
        public int rightType;

        public HeroNode(int id, String name) {
            this.id = id;
            this.name = name;
        }

        @Override
        public String toString() {
            return "HeroNode{" +
                    "id=" + id +
                    ", name='" + name + '\'' +
                    '}';
        }
    }

    class ThreadedBinaryTree {
        public HeroNode root;
        public HeroNode pre; // ������һ���ڵ�

        /**
         * ���������������� ����ķ�ʽ������
         */
        public void threadeNodes() {
            // �� root ��ʼ������Ȼ�� ������
            this.threadeNodes(root);
        }

        private void threadeNodes(HeroNode node) {
            if (node == null) {
                return;
            }
            // �������˳�������Լ�������
            threadeNodes(node.left);
            // �ѵ�������������������Լ�
            // ���Լ��� left �ڵ�Ϊ�գ�������Ϊǰ���ڵ�
            if (node.left == null) {
                node.left = pre;
                node.leftType = 1;
            }

            // ��ΪҪ���ú�̽ڵ㣬ֻ�лص��Լ��ĺ�̽ڵ��ʱ�򣬲��ܰ��Լ�����Ϊǰһ���ĺ�̽ڵ�
            // ��ǰһ���ڵ�� right Ϊ��ʱ������Ҫ�Լ��Ǻ�̽ڵ�
            if (pre != null && pre.right == null) {
                pre.right = node;
                pre.rightType = 1;
            }

            // ���У� 1,3,6,8,10,14
            // ���� 8,3,10,1,14,6
            // ������ý��ͼʾ�Ķ������������������
            // ��Ϊ����������ȱ�����ߣ����� 8 �ǵ�һ������Ľڵ�
            // �� node = 8 ʱ��pre ��û�б���ֵ������Ϊ�ա�������ȷ�ģ���Ϊ 8 ���ǵ�һ���ڵ�
            // �� 8 �������֮�󣬴��� 3 ʱ
            // �� node = 3 ʱ��pre ����ֵΪ 8 �ˡ�
            pre = node;
            threadeNodes(node.right);
        }
    }

    @Test
    public void threadeNodesTest() {
        HeroNode n1 = new HeroNode(1, "�ν�");
        HeroNode n3 = new HeroNode(3, "����");
        HeroNode n6 = new HeroNode(6, "¬��");
        HeroNode n8 = new HeroNode(8, "�ֳ�2");
        HeroNode n10 = new HeroNode(10, "�ֳ�3");
        HeroNode n14 = new HeroNode(14, "�ֳ�4");
        n1.left = n3;
        n1.right = n6;
        n3.left = n8;
        n3.right = n10;
        n6.left= n14;

        ThreadedBinaryTree tree = new ThreadedBinaryTree();
        tree.root = n1;

        tree.threadeNodes();

        // ��֤��
        HeroNode left = n10.left;
        HeroNode right = n10.right;
        System.out.println("10 �Žڵ��ǰ���ڵ㣺" + left.id);
        System.out.println("10 �Žڵ�ĺ�̽ڵ㣺" + right.id);
    }
}
