// 70.satır

			// temporary storage
			RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            triple.rgbtBlue = 80;
            triple.rgbtGreen = 00;
            triple.rgbtRed = 80;
            
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

// 82.satır
