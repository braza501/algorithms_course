import java.util.ArrayList;
import java.util.Stack;
import java.util.TreeMap;

/**
 * Created by Admin on 12.10.2015.
 */
public class Expression {

    public static ArrayList<String> toArrayList(String exp) {

        exp = exp.replaceAll(" ", "");
        ArrayList<String> result = new ArrayList<>();
        StringBuilder digits = new StringBuilder();

        for (int i = 0; i < exp.length(); i++) {
            String temp = String.valueOf(exp.charAt(i));

            if (temp.matches("[0-9]")) {
                digits.append(temp);
            } else if(temp.matches("[+-/*()]")){
                if (!digits.toString().isEmpty()) {
                    result.add(digits.toString());
                    digits = new StringBuilder();
                }
                result.add(temp);
            }
            else{
                throw new IllegalArgumentException("Unknown symbol");
            }
        }
        if (!digits.toString().isEmpty())
            result.add(digits.toString());

        Stack<String> braces = new Stack<>();
        if (result.get(0).matches("[+-/*]") || result.get(result.size() - 1).matches("[+-/*]"))
            throw new IllegalArgumentException("Incorrect operator");
        for (int i = 1; i < result.size() - 1; i++) {
            if (result.get(i).matches("[+-/*]") && (!result.get(i - 1).matches("[0-9()]*") || !result.get(i + 1).matches("[0-9()]*")))
                throw new IllegalArgumentException("Incorrect operator");
        }
        for (int i = 0; i < result.size(); i++) {
            if (result.get(i).equals("("))
                braces.push("(");
            else if (result.get(i).equals(")")) {
                if (braces.empty())
                    throw new IllegalArgumentException("Illegal sequence of braces!");
                braces.pop();
            }
        }

        if (!braces.empty())
            throw new IllegalArgumentException("Illegal sequence of braces!");
        return result;
    }


}
