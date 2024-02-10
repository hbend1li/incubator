int split(String &str)
{
    String strs[20];
    int StringCount = 0;

    // Split the string into substrings
    while (str.length() > 0)
    {
        int index = str.indexOf(' ');
        if (index == -1) // No space found
        {
            strs[StringCount++] = str;
            break;
        }
        else
        {
            strs[StringCount++] = str.substring(0, index);
            str = str.substring(index + 1);
        }
    }
}