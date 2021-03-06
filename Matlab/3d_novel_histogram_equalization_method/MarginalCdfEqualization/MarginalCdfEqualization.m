function MarginalCdfEqualization(image_path)
input_img = imread(image_path);
input_luminance_pdf = CalculateLuminancePdf(input_img,'Original Image Luminance PDF');
CalculateLuminanceCdf(input_luminance_pdf,'Original Image Luminance CDF');
figure('Name','Original Image','Numbertitle','off')
imshow(input_img);
red_channel = input_img(:,:,1);
green_channel = input_img(:,:,2);
blue_channel = input_img(:,:,3);
red_pdf = CalculateChannelPdf(red_channel);
green_pdf = CalculateChannelPdf(green_channel);
blue_pdf = CalculateChannelPdf(blue_channel);
red_cdf = CalculateChannelCdf(red_pdf);
green_cdf = CalculateChannelCdf(green_pdf);
blue_cdf = CalculateChannelCdf(blue_pdf);
image_size = size(input_img);
width = image_size(1,1);
height = image_size(1,2);
output_img = zeros(width,height,3,'uint8');
L = 256;
for i=1:width
    for j=1:height
        red = input_img(i,j,1);
        green = input_img(i,j,2);
        blue = input_img(i,j,3);
        rgb_cdf = red_cdf(red+1) * green_cdf(green+1) * blue_cdf(blue+1);
        red_l = double(red + 1);
        green_l = double(green + 1);
        blue_l = double(blue + 1);
        a = 1;
        b = (red_l + green_l + blue_l);
        c = (red_l*green_l + red_l*blue_l + green_l*blue_l);
        d = (red_l*green_l*blue_l - ((L^3)*rgb_cdf));        
        r = cubic(a,b,c,d);
        k = r(imag(r)==0);
        k = k(1,1);                      
        red_output = red + k;
        green_output = green + k;
        blue_output = blue + k;
        output_img(i,j,:) = [red_output green_output blue_output];
    end
end
figure('Name','Marginal-CDF Equalized Image', 'Numbertitle', 'off');
imshow(output_img);
output_luminance_pdf = CalculateLuminancePdf(output_img,'Marginal-CDF Equalized Image Luminance PDF');
CalculateLuminanceCdf(output_luminance_pdf,'Marginal-CDF Equalized Image Luminance CDF');
end