void Min(cell *RangeStart, cell *RangeEnd)
    {
        cell *temp = RangeStart;
        int sum = 0;
        int MIN = 0;
        while (temp != NULL && temp != RangeEnd)
        {

            sum = c - '0'; // Convert character to integer

            if (Min > sum)
            {
                Min = sum;
            }
            temp = temp->next;
        }
        if (temp == NULL)
        {

            sum = 0;
            temp = RangeStart;

            while (temp != NULL && temp != RangeEnd)
            {

                sum = c - '0'; // Convert character to integer
                if (Min > sum)
                {
                    Min = sum;
                }

                temp = temp->down;
            }
            if (temp == NULL)
            {
                return;
            }
            else
            {

                sum = c - '0'; // Convert character to integer

                if (Min > sum)
                {
                    Min = sum;
                }
                temp->value = Min;
            }
        }
        else
        {

            sum = c - '0'; // Convert character to integer
            if (Min > sum)
            {
                Min = sum;
            }

            temp->value = Min;
        }
    }