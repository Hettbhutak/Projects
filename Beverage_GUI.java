import javax.swing.JOptionPane;
import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.JOptionPane;
import javax.swing.JOptionPane;
class Beverage {
private String size;
private double price;
private int amount;

    public Beverage(String size,int amount) {
        super();
        this.size = size;
        this.amount = amount;
        price = 0.0;
    }

    public String getSize() {
        return size;
    }
    public void setSize(String size) {
        this.size = size;
    }
    public double getPrice() {
        return price;
    }
    public void setPrice(double price) {
        this.price = price;
    }
    public int getAmount() {
        return amount;
    }
    public void setAmount(int amount) {
        this.amount = amount;
    }

    @Override
    public String toString() {
        return String.format("%d %s glass(es) of ",this.getAmount(),this.getSize());
    }
}
class Coffee extends Beverage {
private boolean milk;

 public Coffee(String size,int amount,Label lbl) {
     super(size,amount);
     if(JOptionPane.showConfirmDialog(lbl, "Would you like milk?","Milk",JOptionPane.YES_NO_OPTION)==0) milk=true;
     else milk=false;
     double price;
     if(size.equals("Small")) price=3.5;
     else if(size.equals("Medium")) price=5;
     else price=6.5;
     if(milk) price*=1.5;
     setPrice(price);
 }

 @Override
 public String toString() {
     if(milk) return super.toString()+" Coffee with milk";
     else return super.toString()+" Coffee";
 }
}

class Juice extends Beverage {
private String fruit;
String[] fruits = {"Apple","Orange","Pineapple"};

public Juice(String size,int amount,Label lbl) {
    super(size,amount);
    try {
        fruit = (String) JOptionPane.showInputDialog(lbl,"Select a fruit.","Select a fruit",
                JOptionPane.QUESTION_MESSAGE,null,fruits,fruits[0]);
        //Creates a pop up that asks to the user, from which fruit he/she wants his/her juice. Takes lbl as a paramater to display the pop up on the frame
        //If he/she clicks on "OK" following codes will be executed.
        double price;
        if(size.equals("Small")) price=5.0;
        else if(size.equals("Medium")) price=7.0;
        else price=9.0;
        if(fruit.equals("Orange")) price*=1.25;
        if(fruit.equals("Pineapple")) price*=1.5;
        setPrice(price);
    }
    catch(NullPointerException e) {
    }
}

@Override
public String toString() {
    return super.toString()+fruit+" juice";
}
}

class Label extends JFrame implements ActionListener{
private static final long serialVersionUID = 1L;
private JLabel lblSize,lblBev,lblGlass,lblReport;
private JComboBox size;
private JRadioButton rdJuice,rdWater,rdTea,rdCoffee;
private ButtonGroup btnGroup;
private JTextField txtGlass;
private JButton btnAdd,btnOrder;
int amount_of;
ArrayList list_of_bvr = new ArrayList();

public Label() {
    setLayout(null);
    setSize(600,400);
    setLocationRelativeTo(null);
    setTitle("Order");
    init();
    btnAdd.addActionListener(this);
    btnOrder.addActionListener(this);
    setVisible(true);
}

public void init() {
    lblSize = new JLabel("Select size:");// a JLabel that labels the comboBox
    lblSize.setSize(250, 50);
    lblSize.setLocation(100, 10);
    add(lblSize);

    String[] sizes = {"Small","Medium","Large"};
    size = new JComboBox<String>(sizes);//
    size.setSelectedIndex(0);//default selection is small
    size.setSize(100, 25);
    size.setLocation(100, 50);
    add(size);

    lblBev = new JLabel("Select which type of beverage you want to order:");//a JLabel that labels the radioButtons
    lblBev.setSize(500, 50);
    lblBev.setLocation(100, 75);
    add(lblBev);

    btnGroup = new ButtonGroup();

    rdJuice = new JRadioButton("Juice");
    rdJuice.setSize(75, 50);
    rdJuice.setLocation(100, 110);
    add(rdJuice);

    rdWater = new JRadioButton("Water");
    rdWater.setSize(75, 50);
    rdWater.setLocation(175, 110);
    add(rdWater);

    rdTea = new JRadioButton("Tea");
    rdTea.setSize(75, 50);
    rdTea.setLocation(250, 110);
    add(rdTea);

    rdCoffee = new JRadioButton("Coffee");
    rdCoffee.setSize(75, 50);
    rdCoffee.setLocation(325, 110);
    add(rdCoffee);

    btnGroup.add(rdJuice);
    btnGroup.add(rdWater);
    btnGroup.add(rdTea);
    btnGroup.add(rdCoffee);

    lblGlass = new JLabel("Type how many glasses you want to order:");//a JLabel that labels the Text Field
    lblGlass.setSize(500, 50);
    lblGlass.setLocation(100, 145);
    add(lblGlass);

    txtGlass = new JTextField();//a JTextField to get how many glasses of beverage is the user want
    txtGlass.setSize(300, 25);
    txtGlass.setLocation(100, 185);
    add(txtGlass);

    btnAdd = new JButton("Add");
    btnAdd.setSize(120, 40);
    btnAdd.setLocation(100, 230);
    add(btnAdd);

    btnOrder = new JButton("Order");
    btnOrder.setSize(120, 40);
    btnOrder.setLocation(280, 230);
    btnOrder.setEnabled(false);
    add(btnOrder);

    lblReport = new JLabel();//will be showing report of the beverages that added.
    lblReport.setSize(500, 50);
    lblReport.setLocation(100, 270);
    add(lblReport);
}

@Override
public void actionPerformed(ActionEvent e) {
    String size_of = (String)size.getSelectedItem();
    if(e.getSource().equals(btnAdd)) {
        if( rdJuice.isSelected() || rdTea.isSelected() || rdCoffee.isSelected() || rdWater.isSelected() && !(txtGlass.getText().isEmpty())) {
            try {
                amount_of  = Integer.parseInt(txtGlass.getText().trim());
                Beverage bvg;
                if(rdJuice.isSelected())  { bvg = new Juice(size_of,amount_of,this); }
                else if(rdWater.isSelected())  { bvg = new Water(size_of,amount_of,this); }
                else if(rdTea.isSelected())    { bvg = new Tea(size_of,amount_of,this); }
                else { bvg = new Coffee(size_of,amount_of,this); }
                txtGlass.setText(null);
                list_of_bvr.add(bvg);
                lblReport.setText(bvg.toString()+" added");
                btnGroup.clearSelection();
                btnOrder.setEnabled(true);
            }
            catch(NumberFormatException e1) {//if written data in TextField can't be converted to an integer[String,char,double etc...]
                JOptionPane.showMessageDialog(this, "Enter an integer as amount");
            }
        }
        else { JOptionPane.showMessageDialog(this, "Choose a beverage type and enter an amount");
            //if none of the radio buttons are selected or the textField is empty
        }
    }
    if(e.getSource().equals(btnOrder)) {
        String report = "";
        double pay=0.0;
        for(int i=0;i<list_of_bvr.size();i++) {
            Beverage bvgi = list_of_bvr.get(i);
            report += bvgi.toString();
            double totalprice_of_bvg = bvgi.getAmount() * bvgi.getPrice();
            pay += totalprice_of_bvg;
            report = report + " - "+totalprice_of_bvg+" TL\n";
        }
        JOptionPane.showMessageDialog(this, report);
        JOptionPane.showMessageDialog(this,	 "You should pay "+pay+" TL");
        lblReport.setText(null);
        btnOrder.setEnabled(false);
        list_of_bvr.clear();
    }
}

public static void main(String[] args) {
    new Label();
}
}

class Tea extends Beverage {
private boolean sugar;

public Tea(String size,int amount,Label lbl) {
    super(size,amount);
    if(JOptionPane.showConfirmDialog(lbl, "Would you like sugar?","Sugar",JOptionPane.YES_NO_OPTION)==0) sugar=true;
    else sugar=false;
    double price;
    if(size.equals("Small")) price=3.0;
    else if(size.equals("Medium")) price=4.0;
    else price=5.0;
    if(sugar) price*=1.25;
    setPrice(price);
}

@Override
public String toString() {
    if(sugar) return super.toString()+"Tea with sugar";
    else return super.toString()+"Tea";
}
}

class Water extends Beverage {
private boolean iced;

public Water(String size,int amount,Label lbl) {
    super(size,amount);
    if(JOptionPane.showConfirmDialog(lbl, "Would you like ice?","Ice",JOptionPane.YES_NO_OPTION)==0) iced=true;
    else iced=false;
    double price;
    if(size.equals("Small")) price=1.0;
    else if(size.equals("Medium")) price=2.0;
    else price=3.0;
    if(iced) price*=1.25;
    setPrice(price);
}

@Override
public String toString() {
    if(iced) return super.toString()+"Water with ice";
    else return super.toString()+"Water";
}
}
